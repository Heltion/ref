optional<vector<vector<pair<int, bool>>>> undirected_walks(
    int n,
    const vector<pair<int, int>>& edges) {
  int m = ssize(edges);
  vector<vector<pair<int, bool>>> res;
  if (not m) {
    return res;
  }
  vector<vector<pair<int, bool>>> g(n);
  for (int i = 0; i < m; i += 1) {
    auto [u, v] = edges[i];
    g[u].emplace_back(i, true);
    g[v].emplace_back(i, false);
  }
  for (int i = 0; i < n; i += 1) {
    if (g[i].size() % 2) {
      return {};
    }
  }
  vector<pair<int, bool>> walk;
  vector<bool> visited(m);
  vector<int> cur(n);
  function<void(int)> dfs = [&](int u) {
    for (int& i = cur[u]; i < ssize(g[u]);) {
      auto [j, d] = g[u][i];
      if (not visited[j]) {
        visited[j] = true;
        dfs(d ? edges[j].second : edges[j].first);
        walk.emplace_back(j, d);
      } else {
        i += 1;
      }
    }
  };
  for (int i = 0; i < n; i += 1) {
    dfs(i);
    if (not walk.empty()) {
      ranges::reverse(walk);
      res.emplace_back(move(walk));
    }
  }
  return res;
}
optional<vector<vector<int>>> directed_walks(
    int n,
    const vector<pair<int, int>>& edges) {
  int m = ssize(edges);
  vector<vector<int>> res;
  if (not m) {
    return res;
  }
  vector<int> d(n);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i += 1) {
    auto [u, v] = edges[i];
    g[u].push_back(i);
    d[v] += 1;
  }
  for (int i = 0; i < n; i += 1) {
    if (ssize(g[i]) != d[i]) {
      return {};
    }
  }
  vector<int> walk;
  vector<int> cur(n);
  vector<bool> visited(m);
  function<void(int)> dfs = [&](int u) {
    for (int& i = cur[u]; i < ssize(g[u]);) {
      int j = g[u][i];
      if (not visited[j]) {
        visited[j] = true;
        dfs(edges[j].second);
        walk.push_back(j);
      } else {
        i += 1;
      }
    }
  };
  for (int i = 0; i < n; i += 1) {
    dfs(i);
    if (not walk.empty()) {
      ranges::reverse(walk);
      res.emplace_back(move(walk));
    }
  }
  return res;
}