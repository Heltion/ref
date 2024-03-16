vector<vector<int>> two_vertex_connected_components(const vector<vector<int>>& adj) {
  int n = adj.size();
  vector<int> pos(n, -1), stack;
  vector<vector<int>> res;
  auto dfs = [&](auto& dfs, int u, int p) -> int {
    int low = pos[u] = stack.size();
    bool cut = ~p;
    stack.push_back(u);
    for (int v : adj[u]) {
      if (v == p) continue;
      if (~pos[v]) {
        low = min(low, pos[v]);
        continue;
      }
      int end = stack.size(), low_v = dfs(dfs, v, u);
      low = min(low, low_v);
      if (low_v >= pos[u] and exchange(cut, true)) {
        res.emplace_back(stack.begin() + end, stack.end());
        res.back().push_back(u);
        stack.resize(end);
      }
    }
    return low;
  };
  for (int i = 0; i < n; i += 1)
    if (pos[i] == -1) {
      dfs(dfs, i, -1);
      res.emplace_back(move(stack));
    }
  return res;
}