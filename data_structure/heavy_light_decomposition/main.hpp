template <class T, auto bop, auto e>
struct SegmentTree {
  int n;
  vector<T> s;
  SegmentTree(int n) : n(n), s(n * 2, e()) {}
  void set(int i, T v) {
    for (s[i += n] = v; i /= 2;) s[i] = bop(s[i * 2], s[i * 2 + 1]);
  }
  T product(int l, int r) {
    T rl = e(), rr = e();
    for (l += n, r += n + 1; l != r; l /= 2, r /= 2) {
      if (l % 2) rl = bop(rl, s[l++]);
      if (r % 2) rr = bop(s[--r], rr);
    }
    return bop(rl, rr);
  }
};
struct HeavyLigthDecomposition {
  vector<int> p, pos, top;
  HeavyLigthDecomposition(const vector<vector<int>>& adj) {
    int n = adj.size(), m = 0;
    p.resize(n, -1);
    pos.resize(n);
    top.resize(n);
    vector<int> size(n, 1), h(n, -1);
    auto dfs0 = [&](auto& dfs, int u) -> void {
      for (int v : adj[u]) {
        if (v == p[u]) continue;
        p[v] = u;
        dfs(dfs, v);
        size[u] += size[v];
        if (h[u] == -1 or size[h[u]] < size[v]) h[u] = v;
      }
    };
    dfs0(dfs0, 0);
    auto dfs1 = [&](auto& dfs, int u) -> void {
      pos[u] = m++;
      if (~h[u]) {
        top[h[u]] = top[u];
        dfs(dfs, h[u]);
      }
      for (int v : adj[u]) {
        if (v == p[u] or v == h[u]) continue;
        dfs(dfs, top[v] = v);
      }
    };
    dfs1(dfs1, top[0] = 0);
  }
  vector<tuple<int, int, bool>> dec(int u, int v) {
    vector<tuple<int, int, bool>> pu, pv;
    while (top[u] != top[v]) {
      if (pos[u] > pos[v]) {
        pu.emplace_back(pos[top[u]], pos[u], true);
        u = p[top[u]];
      } else {
        pv.emplace_back(pos[top[v]], pos[v], false);
        v = p[top[v]];
      }
    }
    if (pos[u] <= pos[v])
      pv.emplace_back(pos[u], pos[v], false);
    else
      pu.emplace_back(pos[v], pos[u], true);
    ranges::reverse(pv);
    pu.insert(pu.end(), pv.begin(), pv.end());
    return pu;
  }
};