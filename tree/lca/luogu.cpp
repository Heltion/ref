// https://www.luogu.com.cn/problem/P3379
#include <bits/stdc++.h>
using namespace std;

struct LeastCommonAncestor {
  RangeMinimumQuery rmq;
  vector<int> p, time, a, par;
  LeastCommonAncestor(int root, const vector<vector<int>> &g) {
    int n = g.size();
    time.resize(n, -1);
    par.resize(n, -1);
    function<void(int)> dfs = [&](int u) {
      time[u] = p.size();
      p.push_back(u);
      for (int v : g[u]) {
        if (time[v] == -1) {
          par[v] = u;
          dfs(v);
        }
      }
    };
    dfs(root);
    a.resize(n);
    for (int i = 1; i < n; i += 1) { a[i] = time[par[p[i]]]; }
    rmq = RangeMinimumQuery(a);
  }
  int query(int u, int v) {
    if (u == v) { return u; }
    if (time[u] > time[v]) { swap(u, v); }
    return p[rmq.query(time[u] + 1, time[v] + 1)];
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, s;
  cin >> n >> m >> s;
  vector<vector<int>> g(n);
  for (int i = 1, u, v; i < n; i += 1) {
    cin >> u >> v;
    u -= 1;
    v -= 1;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  LeastCommonAncestor lca(s - 1, g);
  for (int i = 0, a, b; i < m; i += 1) {
    cin >> a >> b;
    cout << lca.query(a - 1, b - 1) + 1 << "\n";
  }
}