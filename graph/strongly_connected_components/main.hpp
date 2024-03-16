vector<vector<int>> strongly_connected_components(const vector<vector<int>>& adj) {
  int n = adj.size();
  vector<bool> done(n);
  vector<int> pos(n, -1), stack;
  vector<vector<int>> res;
  auto dfs = [&](auto& dfs, int u) -> int {
    int low = pos[u] = stack.size();
    stack.push_back(u);
    for (int v : adj[u])
      if (not done[v]) low = min(low, ~pos[v] ? pos[v] : dfs(dfs, v));
    if (low == pos[u]) {
      res.emplace_back(stack.begin() + low, stack.end());
      for (int v : res.back()) done[v] = true;
      stack.resize(low);
    }
    return low;
  };
  for (int i = 0; i < n; i += 1)
    if (not done[i]) dfs(dfs, i);
  ranges::reverse(res);
  return res;
}