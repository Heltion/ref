optional<vector<pair<int, bool>>> undirected_eulerian_path(int n, const vector<pair<int, int>>& e) {
  vector<pair<int, bool>> res;
  if (e.empty()) return res;
  vector<vector<pair<int, bool>>> adj(n);
  for (int i = 0; i < ssize(e); i += 1) {
    auto [u, v] = e[i];
    adj[u].emplace_back(i, true);
    adj[v].emplace_back(i, false);
  }
  int s = -1, odd = 0;
  for (int i = 0; i < n; i += 1) {
    if (ssize(adj[i]) % 2 == 0) continue;
    if (odd++ >= 2) return {};
    s = i;
  }
  for (int i = 0; i < n and s == -1; i += 1)
    if (not adj[i].empty()) s = i;
  vector<bool> visited(e.size());
  auto dfs = [&](auto& dfs, int u) -> void {
    while (not adj[u].empty()) {
      auto [j, k] = adj[u].back();
      adj[u].pop_back();
      if (visited[j]) continue;
      visited[j] = true;
      dfs(dfs, k ? e[j].second : e[j].first);
      res.emplace_back(j, k);
    }
  };
  dfs(dfs, s);
  if (res.size() != e.size()) return {};
  ranges::reverse(res);
  return res;
}