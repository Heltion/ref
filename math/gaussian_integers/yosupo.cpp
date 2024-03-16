// https://judge.yosupo.jp/problem/gcd_of_gaussian_integers
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
struct GaussInteger {
  i64 x, y;
  i64 norm() { return x * x + y * y; }
  bool operator!=(i64 r) { return y or x != r; }
  GaussInteger operator~() { return {x, -y}; }
  GaussInteger operator-(GaussInteger gi) { return {x - gi.x, y - gi.y}; }
  GaussInteger operator*(GaussInteger gi) { return {x * gi.x - y * gi.y, x * gi.y + y * gi.x}; }
  GaussInteger operator/(GaussInteger gi) {
    auto [x, y] = operator*(~gi);
    auto div_floor = [&](i64 x, i64 y) { return x / y - (x % y < 0); };
    auto div_round = [&](i64 x, i64 y) { return div_floor(2 * x + y, 2 * y); };
    return {div_round(x, gi.norm()), div_round(y, gi.norm())};
  }
  GaussInteger operator%(GaussInteger gi) { return operator-(gi*(operator/(gi))); }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    i64 a0, b0, a1, b1;
    cin >> a0 >> b0 >> a1 >> b1;
    auto [a, b] = __gcd(GaussInteger{a0, b0}, GaussInteger{a1, b1});
    cout << a << " " << b << "\n";
  }
}