// https://www.luogu.com.cn/problem/P1883
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
f64 simpson(auto& f, f64 l, f64 r) { return (r - l) * (f(l) + f(r) + 4 * f(midpoint(l, r))) / 6; }
f64 adaptive_simpson(auto&& f, f64 l, f64 r, f64 eps) {
  f64 m = midpoint(l, r);
  f64 s = simpson(f, l, r);
  f64 sl = simpson(f, l, m);
  f64 sr = simpson(f, m, r);
  f64 d = sl + sr - s;
  if (abs(d) < 15 * eps) return (sl + sr) + d / 15;
  return adaptive_simpson(f, l, m, eps / 2) + adaptive_simpson(f, m, r, eps / 2);
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  cout << fixed << setprecision(6);
  f64 a, b, c, d, l, r;
  cin >> a >> b >> c >> d >> l >> r;
  cout << adaptive_simpson([&](f64 x) { return (c * x + d) / (a * x + b); }, l, r, 1e-6);
}
