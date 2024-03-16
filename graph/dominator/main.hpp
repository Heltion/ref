vector<int> dominator(const vector<vector<int>> &adj, int s) {
  int n = adj.size();
  vector<int> pos(n, -1), p, label(n), dom(n), sdom(n), dsu(n), par(n);
  vector<vector<int>> rg(n), bucket(n);
  auto dfs = [&](auto &dfs, int u) -> void {
    int t = p.size();
    p.push_back(u);
    label[t] = sdom[t] = dsu[t] = pos[u] = t;
    for (int v : adj[u]) {
      if (pos[v] == -1) {
        dfs(dfs, v);
        par[pos[v]] = t;
      }
      rg[pos[v]].push_back(t);
    }
  };
  dfs(dfs, s);
  auto find = [&](auto &find, int u, int x) {
    if (u == dsu[u]) return x ? -1 : u;
    int v = find(find, dsu[u], x + 1);
    if (v < 0) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
  };
  for (int i = 0; i < n; i += 1) dom[i] = i;
  for (int i = ssize(p) - 1; i >= 0; i -= 1) {
    for (int j : rg[i]) sdom[i] = min(sdom[i], sdom[find(find, j, 0)]);
    if (i) bucket[sdom[i]].push_back(i);
    for (int k : bucket[i]) {
      int j = find(find, k, 0);
      dom[k] = sdom[j] == sdom[k] ? sdom[j] : j;
    }
    if (i > 1) dsu[i] = par[i];
  }
  for (int i = 1; i < ssize(p); i += 1)
    if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
  vector<int> res(n, -1);
  res[s] = s;
  for (int i = 1; i < ssize(p); i += 1) res[p[i]] = p[dom[i]];
  return res;
}