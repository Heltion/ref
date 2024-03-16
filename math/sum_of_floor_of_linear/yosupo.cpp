// https://judge.yosupo.jp/problem/sum_of_floor_of_linear
#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) (void)(0)
#endif
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double_t;
i64 sum_of_floor(i64 n, i64 m, i64 a, i64 b) {
  i64 res = 0;
  while (n) {
    res += a / m * n * (n - 1) / 2;
    a %= m;
    res += b / m * n;
    b %= m;
    i64 y = a * n + b;
    if (y < m) break;
    tie(n, m, a, b) = tuple(y / m, a, m, y % m);
  }
  return res;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    i64 n, m, a, b;
    cin >> n >> m >> a >> b;
    cout << sum_of_floor(n, m, a, b) << "\n";
  }
}