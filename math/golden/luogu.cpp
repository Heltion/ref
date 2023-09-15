// https://www.luogu.com.cn/problem/P3382
#include <bits/stdc++.h>
using namespace std;
using f64 = double;
template <int step> f64 golden_search(function<f64(f64)> f, f64 l, f64 r) {
  f64 ml = (numbers::phi - 1) * l + (2 - numbers::phi) * r;
  f64 mr = l + r - ml;
  f64 fml = f(ml), fmr = f(mr);
  for (int i = 0; i < step; i += 1)
    if (fml > fmr) {
      l = ml;
      ml = mr;
      fml = fmr;
      fmr = f(mr = (numbers::phi - 1) * r + (2 - numbers::phi) * l);
    } else {
      r = mr;
      mr = ml;
      fmr = fml;
      fml = f(ml = (numbers::phi - 1) * l + (2 - numbers::phi) * r);
    }
  return midpoint(l, r);
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  f64 l, r;
  cin >> l >> r;
  vector<f64> c(n + 1);
  for (f64 &ci : c) { cin >> ci; }
  function<f64(f64)> f = [&](f64 x) {
    f64 y = 0;
    for (f64 ci : c) { y = y * x + ci; }
    return -y;
  };
  cout << fixed << setprecision(20) << golden_search<50>(f, l, r);
}