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
using i128 = __int128_t;
template <typename T>
tuple<T, T, T> exgcd(T a, T b) {
  T x = 1, y = 0, x1 = 0, y1 = 1;
  while (b) {
    T q = a / b;
    tie(x, x1) = pair(x1, x - q * x1);
    tie(y, y1) = pair(y1, x - q * y1);
    tie(a, b) = pair(b, a - q * b);
  }
  return {a, x, y};
}
template <typename T>
optional<pair<T, T>> crt(T a0, T b0, T a1, T b1) {
  auto [d, x, y] = exgcd(a0, a1);
  if ((b1 - b0) % d) return {};
  T a = a0 / d * a1, b = (b1 - b0) / d * x % (a1 / d);
  if (b < 0) b += a1 / d;
  b = (a0 * b + b0) % a;
  if (b < 0) b += a;
  return {{a, b}};
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n;
  cin >> n;
  i128 x = 1, y = 0;
  for (int i = 0; i < n; i += 1) {
    i64 a, b;
    cin >> a >> b;
    tie(x, y) = crt<i128>(x, y, a, b % a).value();
  }
  cout << i64(y);
}