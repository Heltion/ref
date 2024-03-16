// https://judge.yosupo.jp/problem/biconnected_components
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
  auto bccs = two_vertex_connected_components(g);
  cout << bccs.size() << "\n";
  for (auto bcc : bccs) {
    cout << bcc.size();
    for (int u : bcc) cout << " " << u;
    cout << "\n";
  }
}