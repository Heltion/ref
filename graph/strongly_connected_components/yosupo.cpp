// https://judge.yosupo.jp/problem/scc
#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) (void)(0)
#endif
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double_t;
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
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0, u, v; i < m; i += 1) {
    cin >> u >> v;
    adj[u].push_back(v);
  }
  auto sccs = strongly_connected_components(adj);
  cout << sccs.size() << "\n";
  for (auto scc : sccs) {
    cout << scc.size();
    for (int u : scc) cout << " " << u;
    cout << "\n";
  }
}