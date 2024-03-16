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
template <int step>
f64 local_minimum(auto& f, f64 l, f64 r) {
  auto get = [&](f64 l, f64 r) { return (numbers::phi - 1) * l + (2 - numbers::phi) * r; };
  f64 ml = get(l, r), mr = get(r, l), fml = f(ml), fmr = f(mr);
  for (int _ = 0; _ < step; _ += 1)
    if (fml > fmr) {
      l = exchange(ml, mr);
      fml = exchange(fmr, f(mr = get(r, l)));
    } else {
      r = exchange(mr, ml);
      fmr = exchange(fml, f(ml = get(l, r)));
    }
  return midpoint(l, r);
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  cout << fixed << setprecision(4);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> fs(n);
    for (auto& [a, b, c] : fs) cin >> a >> b >> c;
    auto f = [&](f64 x) {
      f64 y = -1 / 0.;
      for (auto [a, b, c] : fs) y = max(y, a * x * x + b * x + c);
      return y;
    };
    cout << f(local_minimum<100>(f, 0, 1000)) << "\n";
  }
}
