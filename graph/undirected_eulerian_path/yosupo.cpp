// https://judge.yosupo.jp/problem/eulerian_trail_undirected
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
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> e(m);
    for (auto& [u, v] : e) cin >> u >> v;
    auto res = undirected_eulerian_path(n, e);
    if (not res.has_value()) {
      cout << "No\n";
      continue;
    }
    cout << "Yes\n";
    auto p = res.value();
    cout << (p.empty() ? 0 : p[0].second ? e[p[0].first].first : e[p[0].first].second);
    for (auto [i, j] : p) cout << " " << (j ? e[i].second : e[i].first);
    cout << "\n";
    for (auto [i, _] : p) cout << i << " ";
    cout << "\n";
  }
}