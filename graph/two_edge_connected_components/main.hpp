vector<vector<int>> two_edge_connected_components(const vector<vector<int>>& adj) {
  int n = adj.size();
  vector<int> pos(n, -1), stack;
  vector<vector<int>> res;
  auto dfs = [&](auto& dfs, int u, int p) -> int {
    int low = pos[u] = stack.size();
    bool mul = false;
    stack.push_back(u);
    for (int v : adj[u]) {
      if (~pos[v]) {
        if (v != p or exchange(mul, true)) low = min(low, pos[v]);
        continue;
      }
      low = min(low, dfs(dfs, v, u));
    }
    if (low == pos[u]) {
      res.emplace_back(stack.begin() + low, stack.end());
      stack.resize(low);
    }
    return low;
  };
  for (int i = 0; i < n; i += 1)
    if (pos[i] == -1) dfs(dfs, i, -1);
  return res;
}