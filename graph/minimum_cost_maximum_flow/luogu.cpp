// https://www.luogu.com.cn/problem/P3381
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
struct MinimumCostMaximumFlow {
  int n;
  vector<tuple<int, int, i64, i64>> e;
  vector<vector<int>> adj;
  MinimumCostMaximumFlow(int n) : n(n), adj(n) {}
  int add_edge(int u, int v, i64 f, i64 c) {
    int i = e.size();
    e.emplace_back(u, v, f, c);
    e.emplace_back(v, u, 0, -c);
    adj[u].push_back(i);
    adj[v].push_back(i + 1);
    return i;
  }
  pair<i64, i64> flow(int s, int t) {
    constexpr i64 inf = numeric_limits<i64>::max();
    vector<i64> d, h(n);
    vector<int> p;
    auto dijkstra = [&]() {
      d.assign(n, inf);
      p.assign(n, -1);
      priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> q;
      q.emplace(d[s] = 0, s);
      while (not q.empty()) {
        auto [du, u] = q.top();
        q.pop();
        if (du != d[u]) continue;
        for (int i : adj[u]) {
          auto [_, v, f, c] = e[i];
          if (f and d[v] > d[u] + h[u] - h[v] + c) {
            p[v] = i;
            q.emplace(d[v] = d[u] + h[u] - h[v] + c, v);
          }
        }
      }
      return ~p[t];
    };
    i64 f = 0, c = 0;
    while (dijkstra()) {
      for (int i = 0; i < n; i += 1) h[i] += d[i];
      vector<int> path;
      for (int u = t; u != s; u = get<0>(e[p[u]])) path.push_back(p[u]);
      i64 mf = get<2>(e[ranges::min(path, {}, [&](int i) { return get<2>(e[i]); })]);
      f += mf;
      c += mf * h[t];
      for (int i : path) {
        get<2>(e[i]) -= mf;
        get<2>(e[i ^ 1]) += mf;
      }
    }
    return {f, c};
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  MinimumCostMaximumFlow mcmf(n);
  for (int i = 0, u, v, f, c; i < m; i += 1) {
    cin >> u >> v >> f >> c;
    mcmf.add_edge(u - 1, v - 1, f, c);
  }
  auto [f, c] = mcmf.flow(s - 1, t - 1);
  cout << f << " " << c << "\n";
}