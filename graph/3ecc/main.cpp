vector<vector<int>> three_edge_connected_components(const vector<vector<int>>& g) {
  int n = g.size(), dft = -1;
  vector<int> pre(n, -1), post(n), path(n, -1), low(n), deg(n);
  DisjointSetUnion dsu(n);
  function<void(int, int)> dfs = [&](int u, int p) {
    int pc = 0;
    low[u] = pre[u] = dft += 1;
    for (int v : g[u]) {
      if (v != u and (v != p or pc++)) {
        if (pre[v] != -1) {
          if (pre[v] < pre[u]) {
            deg[u] += 1;
            low[u] = min(low[u], pre[v]);
          } else {
            deg[u] -= 1;
            for (int& p = path[u]; p != -1 and pre[p] <= pre[v] and pre[v] <= post[p];) {
              dsu.merge(u, p);
              deg[u] += deg[p];
              p = path[p];
            }
          }
        } else {
          dfs(v, u);
          if (path[v] == -1 and deg[v] <= 1) {
            low[u] = min(low[u], low[v]);
            deg[u] += deg[v];
          } else {
            if (deg[v] == 0) {
              v = path[v];
            }
            if (low[u] > low[v]) {
              low[u] = min(low[u], low[v]);
              swap(v, path[u]);
            }
            for (; v != -1; v = path[v]) {
              dsu.merge(u, v);
              deg[u] += deg[v];
            }
          }
        }
      }
    }
    post[u] = dft;
  };
  for (int i = 0; i < n; i += 1) {
    if (pre[i] == -1) {
      dfs(i, -1);
    }
  }
  vector<vector<int>> _res(n);
  for (int i = 0; i < n; i += 1) {
    _res[dsu.find(i)].push_back(i);
  }
  vector<vector<int>> res;
  for (auto& res_i : _res) {
    if (not res_i.empty()) {
      res.emplace_back(move(res_i));
    }
  }
  return res;
}