optional<vector<int>> directed_eulerian_path(int n, const vector<pair<int, int>>& e) {
  vector<int> res;
  if (e.empty()) return res;
  vector<vector<int>> adj(n);
  vector<int> in(n);
  for (int i = 0; i < ssize(e); i += 1) {
    auto [u, v] = e[i];
    adj[u].push_back(i);
    in[v] += 1;
  }
  int s = -1;
  for (int i = 0; i < n; i += 1) {
    if (ssize(adj[i]) <= in[i]) continue;
    if (ssize(adj[i]) > in[i] + 1 or ~s) return {};
    s = i;
  }
  for (int i = 0; i < n and s == -1; i += 1)
    if (not adj[i].empty()) s = i;
  auto dfs = [&](auto& dfs, int u) -> void {
    while (not adj[u].empty()) {
      int j = adj[u].back();
      adj[u].pop_back();
      dfs(dfs, e[j].second);
      res.push_back(j);
    }
  };
  dfs(dfs, s);
  if (res.size() != e.size()) return {};
  ranges::reverse(res);
  return res;
}