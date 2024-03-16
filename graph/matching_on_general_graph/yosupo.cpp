// https://judge.yosupo.jp/problem/general_matching
#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) void(0)
#endif
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double_t;
vector<int> matching(const vector<vector<int>> &adj) {
  int n = adj.size(), count = 0;
  vector<int> matched(n, -1), f(n), p(n, -1), mark(n);
  auto argument = [&](int u) {
    while (u != -1) {
      int v = matched[p[u]];
      matched[matched[u] = p[u]] = u;
      u = v;
    }
  };
  auto lca = [&](int u, int v) {
    count += 1;
    while (true) {
      if (u == -1) swap(u, v);
      if (mark[u] == count) return u;
      mark[u] = count;
      u = f[p[matched[u]]];
    }
    return 0;
  };
  for (int i = 0; i < n; i += 1)
    if (matched[i] == -1)
      [&]() {
        vector<int> type(n, -1);
        for (int i = 0; i < n; i += 1) f[i] = i;
        queue<int> q;
        type[i] = 0;
        q.push(i);
        auto up = [&](int u, int v, int w) {
          while (f[u] != w) {
            p[u] = v;
            v = matched[u];
            if (type[v] == 1) {
              type[v] = 0;
              q.push(v);
            }
            f[u] = f[v] = w;
            u = p[v];
          }
        };
        while (not q.empty()) {
          int u = q.front();
          q.pop();
          for (int v : adj[u])
            if (type[v] == -1) {
              p[v] = u;
              type[v] = 1;
              int mv = matched[v];
              if (mv == -1) return argument(v);
            } else if (not type[v] and f[u] != f[v]) {
              int w = lca(u, v);
              up(u, v, w);
              up(v, u, w);
              for (int i = 0; i < n; i += 1) f[i] = f[f[i]];
            }
        }
      }();
  return matched;
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
    adj[v].push_back(u);
  }
  auto res = matching(adj);
  vector<pair<int, int>> vp;
  for (int i = 0; i < n; i += 1)
    if (res[i] != -1 and res[i] > i) vp.emplace_back(i, res[i]);
  cout << vp.size() << "\n";
  for (auto [x, y] : vp) cout << x << " " << y << "\n";
}