// https://judge.yosupo.jp/problem/min_of_mod_of_linear
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
i64 min_of_mod(i64 n, i64 m, i64 a, i64 b, bool rev = false, i64 p = 1, i64 q = 1) {
  if (not a) return b;
  if (rev) {
    if (b < m - a) {
      i64 t = (m - b - 1) / a, d = t * p;
      if (n <= d) return (n - 1) / p * a + b;
      n -= d;
      b += a * t;
    }
    b = m - 1 - b;
  } else {
    if (b >= a) {
      i64 t = (m - b + a - 1) / a, d = (t - 1) * p + q;
      if (n <= d) return b;
      n -= d;
      b += a * t - m;
    }
    b = a - 1 - b;
  }
  return (rev ? m : a) - 1 - min_of_mod(n, a, m % a, b, not rev, (m / a - 1) * p + q, m / a * p + q);
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    i64 n, m, a, b;
    cin >> n >> m >> a >> b;
    cout << min_of_mod(n, m, a, b) << "\n";
  }
}