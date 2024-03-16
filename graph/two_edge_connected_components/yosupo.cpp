// https://judge.yosupo.jp/problem/two_edge_connected_components
#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "debug.h"
#else
#define debug(...) (void)(0)
#endif
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double_t;
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
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0, u, v; i < m; i += 1) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  auto bccs = two_edge_connected_components(g);
  cout << bccs.size() << "\n";
  for (auto bcc : bccs) {
    cout << bcc.size();
    for (int u : bcc) cout << " " << u;
    cout << "\n";
  }
}