// https://judge.yosupo.jp/problem/discrete_logarithm_mod
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
optional<i64> log_mod(i64 x, i64 y, i64 m) {
  if (y == 1 or m == 1) return 0;
  if (not x) return y ? nullopt : optional(1);
  i64 k = 0, z = 1;
  for (i64 d; z != y and (d = gcd(x, m)) != 1; k += 1) {
    if (y % d) return {};
    m /= d;
    y /= d;
    z = z * (x / d) % m;
  }
  if (z == y) return k;
  unordered_map<i64, i64> mp;
  i64 p = 1, n = sqrt(m);
  for (int i = 0; i < n; i += 1, p = p * x % m) mp[y * p % m] = i;
  z = z * p % m;
  for (int i = 1; i <= n; i += 1, z = z * p % m)
    if (mp.contains(z)) return k + i * n - mp[z];
  return {};
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    i64 x, y, m;
    cin >> x >> y >> m;
    cout << log_mod(x, y, m).value_or(-1) << "\n";
  }
}