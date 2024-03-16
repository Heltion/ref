// https://www.luogu.com.cn/problem/P5632
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
i64 stoer_wagner(vector<vector<i64>> &w) {
  int n = w.size();
  if (n == 2) return w[0][1];
  vector<bool> in(n);
  vector<int> add;
  vector<i64> s(n);
  i64 st = 0;
  for (int i = 0; i < n; i += 1) {
    int k = -1;
    for (int j = 0; j < n; j += 1)
      if (not in[j] and (k == -1 or s[j] > s[k])) k = j;
    add.push_back(k);
    st = s[k];
    in[k] = true;
    for (int j = 0; j < n; j += 1) s[j] += w[j][k];
  }
  int x = add.end()[-2], y = add.back();
  if (x == n - 1) swap(x, y);
  for (int i = 0; i < n; i += 1) {
    swap(w[y][i], w[n - 1][i]);
    swap(w[i][y], w[i][n - 1]);
  }
  for (int i = 0; i + 1 < n; i += 1) {
    w[i][x] += w[i][n - 1];
    w[x][i] += w[n - 1][i];
  }
  w.pop_back();
  return min(st, stoer_wagner(w));
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, m;
  cin >> n >> m;
  vector w(n, vector<i64>(n));
  for (int i = 0, u, v, c; i < m; i += 1) {
    cin >> u >> v >> c;
    u -= 1;
    v -= 1;
    w[u][v] += c;
    w[v][u] += c;
  }
  cout << stoer_wagner(w) << "\n";
}