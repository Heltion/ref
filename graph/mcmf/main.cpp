struct MinimumCostMaximumFlow {
  template <typename T>
  using minimum_heap = priority_queue<T, vector<T>, greater<T>>;
  int n;
  vector<Edge> edges;
  vector<vector<int>> g;
  MinimumCostMaximumFlow(int n)
      : n(n), g(n) {}
  int add_edge(int u, int v, i64 f, i64 c) {
    int i = edges.size();
    edges.push_back({u, v, f, c});
    edges.push_back({v, u, 0, -c});
    g[u].push_back(i);
    g[v].push_back(i + 1);
    return i;
  }
  pair<i64, i64> flow(int s, int t) {
    constexpr i64 inf = numeric_limits<i64>::max();
    vector<i64> d, h(n);
    vector<int> p;
    auto dijkstra = [&]() {
      d.assign(n, inf);
      p.assign(n, -1);
      minimum_heap<pair<i64, int>> q;
      q.emplace(d[s] = 0, s);
      while (not q.empty()) {
        auto [du, u] = q.top();
        q.pop();
        if (du > d[u]) {
          continue;
        }
        for (int i : g[u]) {
          auto [_, v, f, c] = edges[i];
          if (f and d[v] > d[u] + h[u] - h[v] + c) {
            p[v] = i;
            q.emplace(d[v] = d[u] + h[u] - h[v] + c, v);
          }
        }
      }
      return ~p[t];
    };
    i64 f = 0, c = 0;
    while (dijkstra()) {
      for (int i = 0; i < n; i += 1) {
        h[i] += d[i];
      }
      vector<int> path;
      for (int u = t; u != s; u = edges[p[u]].u) {
        path.push_back(p[u]);
      }
      i64 mf =
          edges[ranges::min(path, {}, [&](int i) { return edges[i].f; })].f;
      f += mf;
      c += mf * h[t];
      for (int i : path) {
        edges[i].f -= mf;
        edges[i ^ 1].f += mf;
      }
    }
    return {f, c};
  }
};
