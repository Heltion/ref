struct LeastCommonAncestor {
  SparseTable st;
  vector<int> p, time, a, par;
  LeastCommonAncestor(int root, const vector<vector<int>> &g) {
    int n = g.size();
    time.resize(n, -1);
    par.resize(n, -1);
    function<void(int)> dfs = [&](int u) {
      time[u] = p.size();
      p.push_back(u);
      for (int v : g[u]) {
        if (time[v] == -1) {
          par[v] = u;
          dfs(v);
        }
      }
    };
    dfs(root);
    a.resize(n);
    for (int i = 1; i < n; i += 1) { a[i] = time[par[p[i]]]; }
    st = SparseTable(a);
  }
  int query(int u, int v) {
    if (u == v) { return u; }
    if (time[u] > time[v]) { swap(u, v); }
    return p[st.query(time[u] + 1, time[v] + 1)];
  }
};