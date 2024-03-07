#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Edge {
  int u, v;
  i64 f;
};
struct HighestLabelPreflowPush {
  int n;
  vector<vector<int>> g;
  vector<Edge> edges;
  HighestLabelPreflowPush(int n) : n(n), g(n) {}
  int add(int u, int v, i64 f) {
    if (u == v) {
      return -1;
    }
    int i = ssize(edges);
    edges.push_back({u, v, f});
    g[u].push_back(i);
    edges.push_back({v, u, 0});
    g[v].push_back(i + 1);
    return i;
  }
  i64 max_flow(int s, int t) {
    vector<i64> p(n);
    vector<int> h(n), cur(n), count(n * 2);
    vector<vector<int>> pq(n * 2);
    auto push = [&](int i, i64 f) {
      auto [u, v, _] = edges[i];
      if (not p[v] and f) {
        pq[h[v]].push_back(v);
      }
      edges[i].f -= f;
      edges[i ^ 1].f += f;
      p[u] -= f;
      p[v] += f;
    };
    h[s] = n;
    count[0] = n - 1;
    p[t] = 1;
    for (int i : g[s]) {
      push(i, edges[i].f);
    }
    for (int hi = 0;;) {
      while (pq[hi].empty()) {
        if (not hi--) {
          return -p[s];
        }
      }
      int u = pq[hi].back();
      pq[hi].pop_back();
      while (p[u] > 0) {
        if (cur[u] == ssize(g[u])) {
          h[u] = n * 2 + 1;
          for (int i = 0; i < ssize(g[u]); i += 1) {
            auto [_, v, f] = edges[g[u][i]];
            if (f and h[u] > h[v] + 1) {
              h[u] = h[v] + 1;
              cur[u] = i;
            }
          }
          count[h[u]] += 1;
          if (not(count[hi] -= 1) and hi < n) {
            for (int i = 0; i < n; i += 1) {
              if (h[i] > hi and h[i] < n) {
                count[h[i]] -= 1;
                h[i] = n + 1;
              }
            }
          }
          hi = h[u];
        } else {
          int i = g[u][cur[u]];
          auto [_, v, f] = edges[i];
          if (f and h[u] == h[v] + 1) {
            push(i, min(p[u], f));
          } else {
            cur[u] += 1;
          }
        }
      }
    }
    return i64(0);
  }
};
int main() {
  cin.sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  HighestLabelPreflowPush hlpp(n + 1);
  for (int i = 0, u, v; i < m; i += 1) {
    i64 f;
    cin >> u >> v >> f;
    hlpp.add(u, v, f);
  }
  cout << hlpp.max_flow(s, t);
  return 0;
}