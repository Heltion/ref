optional<vector<int>> undirected_circuit(int n,
                                         const vector<pair<int, int>> &edges) {
  int m = edges.size();
  if (not m) { return vector<int>(); }
  vector<bool> visited(m);
  vector<int> res;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i += 1) {
    g[edges[i].first].push_back(i + 1);
    g[edges[i].second].push_back(-i - 1);
  }
  for (int i = 0; i < n; i += 1) {
    if (g[i].size() & 1) { return {}; }
  }
  vector<vector<int>::const_iterator> it(n);
  for (int i = 0; i < n; i += 1) { it[i] = g[i].begin(); }
  function<void(int)> dfs = [&](int u) {
    for (auto &nxt = it[u]; nxt != g[u].end();) {
      int i = abs(*nxt) - 1;
      if (not visited[i]) {
        visited[i] = 1;
        int w = *nxt;
        dfs(*nxt >= 0 ? edges[i].second : edges[i].first);
        res.push_back(-w);
      } else {
        nxt = next(nxt);
      }
    }
  };
  int s = 0;
  while (g[s].empty()) { s += 1; }
  dfs(s);
  if (ssize(res) < m) { return {}; }
  return res;
}

optional<vector<int>> directed_circuit(int n,
                                       const vector<pair<int, int>> &edges) {
  int m = edges.size();
  if (not m) { return vector<int>(); }
  vector<bool> visited(m);
  vector<int> d(n), res;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i += 1) {
    g[edges[i].first].push_back(i);
    d[edges[i].second] += 1;
  }
  for (int i = 0; i < n; i += 1) {
    if (ssize(g[i]) != d[i]) { return {}; }
  }
  vector<vector<int>::const_iterator> it(n);
  for (int i = 0; i < n; i += 1) { it[i] = g[i].begin(); }
  function<void(int)> dfs = [&](int u) {
    for (auto &nxt = it[u]; nxt != g[u].end();) {
      if (not visited[*nxt]) {
        visited[*nxt] = 1;
        int w = *nxt;
        dfs(edges[w].second);
        res.push_back(w);
      } else {
        nxt = next(nxt);
      }
    }
  };
  int s = 0;
  while (g[s].empty()) { s += 1; }
  dfs(s);
  if (ssize(res) < m) { return {}; }
  ranges::reverse(res);
  return res;
}