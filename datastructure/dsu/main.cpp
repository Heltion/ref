struct DisjointSetUnion {
  vector<int> dsu;
  DisjointSetUnion(int n) : dsu(n, -1) {}
  int find(int u) { return dsu[u] < 0 ? u : dsu[u] = find(dsu[u]); }
  void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
      if (dsu[u] > dsu[v]) { swap(u, v); }
      dsu[u] += dsu[v];
      dsu[v] = u;
    }
  }
};
struct RollbackDisjointSetUnion {
  vector<pair<int, int>> stack;
  vector<int> dsu;
  RollbackDisjointSetUnion(int n) : dsu(n, -1) {}
  int find(int u) { return dsu[u] < 0 ? u : find(dsu[u]); }
  int time() { return ssize(stack); }
  bool merge(int u, int v) {
    if ((u = find(u)) == (v = find(v))) { return false; }
    if (dsu[u] < dsu[v]) { swap(u, v); }
    stack.emplace_back(u, dsu[u]);
    dsu[v] += dsu[u];
    dsu[u] = v;
    return true;
  }
  void rollback(int t) {
    while (ssize(stack) > t) {
      auto [u, dsu_u] = stack.back();
      stack.pop_back();
      dsu[dsu[u]] -= dsu_u;
      dsu[u] = dsu_u;
    }
  }
};
