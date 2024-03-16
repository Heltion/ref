// https://uoj.ac/problem/680
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
struct HighestLabelPreflowPush {
  int n;
  vector<vector<int>> adj;
  vector<tuple<int, int, i64>> e;
  HighestLabelPreflowPush(int n) : n(n), adj(n) {}
  int add(int u, int v, i64 f) {
    if (u == v) return -1;
    int i = ssize(e);
    e.emplace_back(u, v, f);
    e.emplace_back(v, u, 0);
    adj[u].push_back(i);
    adj[v].push_back(i ^ 1);
    return i;
  }
  i64 max_flow(int s, int t) {
    vector<i64> p(n);
    vector<int> h(n), cur(n), count(n * 2);
    vector<vector<int>> pq(n * 2);
    auto push = [&](int i, i64 f) {
      auto [u, v, _] = e[i];
      if (not p[v] and f) pq[h[v]].push_back(v);
      get<2>(e[i]) -= f;
      get<2>(e[i ^ 1]) += f;
      p[u] -= f;
      p[v] += f;
    };
    h[s] = n;
    count[0] = n - 1;
    p[t] = 1;
    for (int i : adj[s]) push(i, get<2>(e[i]));
    for (int hi = 0;;) {
      while (pq[hi].empty())
        if (not hi--) return -p[s];
      int u = pq[hi].back();
      pq[hi].pop_back();
      while (p[u] > 0)
        if (cur[u] == ssize(adj[u])) {
          h[u] = n * 2 + 1;
          for (int i = 0; i < ssize(adj[u]); i += 1) {
            auto [_, v, f] = e[adj[u][i]];
            if (f and h[u] > h[v] + 1) {
              h[u] = h[v] + 1;
              cur[u] = i;
            }
          }
          count[h[u]] += 1;
          if (not(count[hi] -= 1) and hi < n)
            for (int i = 0; i < n; i += 1)
              if (h[i] > hi and h[i] < n) {
                count[h[i]] -= 1;
                h[i] = n + 1;
              }
          hi = h[u];
        } else {
          int i = adj[u][cur[u]];
          auto [_, v, f] = e[i];
          if (f and h[u] == h[v] + 1)
            push(i, min(p[u], f));
          else
            cur[u] += 1;
        }
    }
    return 0;
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  HighestLabelPreflowPush hlpp(n);
  for (int i = 0, u, v, f; i < m; i += 1) {
    cin >> u >> v >> f;
    hlpp.add(u - 1, v - 1, f);
  }
  cout << hlpp.max_flow(s - 1, t - 1);
}