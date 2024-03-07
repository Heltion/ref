#define PROBLEM "https://judge.yosupo.jp/problem/gcd_of_gaussian_integers"
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
i64 div_floor(i64 x, i64 y) {
  return x / y - (x % y < 0);
}
i64 div_ceil(i64 x, i64 y) {
  return x / y + (x % y > 0);
}
i64 div_round(i64 x, i64 y) {
  return div_floor(2 * x + y, 2 * y);
}
struct Gauss {
  i64 x, y;
  i64 norm() { return x * x + y * y; }
  bool operator!=(i64 r) { return y or x != r; }
  Gauss operator~() { return {x, -y}; }
  Gauss operator-(Gauss rhs) { return {x - rhs.x, y - rhs.y}; }
  Gauss operator*(Gauss rhs) {
    return {x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x};
  }
  Gauss operator/(Gauss rhs) {
    auto [x, y] = operator*(~rhs);
    return {div_round(x, rhs.norm()), div_round(y, rhs.norm())};
  }
  Gauss operator%(Gauss rhs) { return operator-(rhs*(operator/(rhs))); }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    Gauss g0, g1;
    cin >> g0.x >> g0.y >> g1.x >> g1.y;
    auto g = __gcd(g0, g1);
    cout << g.x << " " << g.y << "\n";
  }
}