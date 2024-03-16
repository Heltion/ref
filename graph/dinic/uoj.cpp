// https://uoj.ac/problem/78
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
struct Dinic {
  int n;
  vector<tuple<int, int, i64>> e;
  vector<vector<int>> adj;
  vector<int> level;
  Dinic(int n) : n(n), adj(n) {}
  int add(int u, int v, int c) {
    int i = e.size();
    e.emplace_back(u, v, c);
    e.emplace_back(v, u, 0);
    adj[u].push_back(i);
    adj[v].push_back(i ^ 1);
    return i;
  }
  i64 max_flow(int s, int t) {
    i64 flow = 0;
    queue<int> q;
    vector<int> cur;
    auto bfs = [&]() {
      level.assign(n, -1);
      level[s] = 0;
      q.push(s);
      while (not q.empty()) {
        int u = q.front();
        q.pop();
        for (int i : adj[u]) {
          auto [_, v, c] = e[i];
          if (c and level[v] == -1) {
            level[v] = level[u] + 1;
            q.push(v);
          }
        }
      }
      return ~level[t];
    };
    auto dfs = [&](auto &dfs, int u, i64 limit) -> i64 {
      if (u == t) return limit;
      i64 res = 0;
      for (int &i = cur[u]; i < ssize(adj[u]) and limit; i += 1) {
        int j = adj[u][i];
        auto [_, v, c] = e[j];
        if (level[v] == level[u] + 1 and c)
          if (i64 d = dfs(dfs, v, min(c, limit)); d) {
            limit -= d;
            res += d;
            get<2>(e[j]) -= d;
            get<2>(e[j ^ 1]) += d;
          }
      }
      return res;
    };
    while (bfs()) {
      cur.assign(n, 0);
      while (i64 f = dfs(dfs, s, numeric_limits<i64>::max())) flow += f;
    }
    return flow;
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int nl, nr, m;
  cin >> nl >> nr >> m;
  int s = 0, t = nl + nr + 1, n = t + 1;
  Dinic dinic(n);
  for (int i = 1; i <= nl; i += 1) dinic.add(s, i, 1);
  for (int i = 1; i <= nr; i += 1) dinic.add(nl + i, t, 1);
  for (int i = 0, u, v; i < m; i += 1) {
    cin >> u >> v;
    dinic.add(u, v + nl, 1);
  }
  int f = dinic.max_flow(s, t);
  cout << f << "\n";
  vector<int> matched(nl + 1);
  for (auto [u, v, f] : dinic.e)
    if (u <= nl and v > nl and not f) {
      matched[u] = v - nl;
    }
  for (int i = 1; i <= nl; i += 1) cout << matched[i] << " ";
}