// https://judge.yosupo.jp/problem/eulerian_trail_directed
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
    auto res = directed_eulerian_path(n, e);
    if (not res.has_value()) {
      cout << "No\n";
      continue;
    }
    cout << "Yes\n";
    auto p = res.value();
    cout << (p.empty() ? 0 : e[p[0]].first);
    for (int i : p) cout << " " << e[i].second;
    cout << "\n";
    for (int i : p) cout << i << " ";
    cout << "\n";
  }
}