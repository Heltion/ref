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