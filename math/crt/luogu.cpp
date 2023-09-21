#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using i128 = __int128_t;
tuple<i64, i64, i64> exgcd(i64 a, i64 b) {
  i64 x = 1, y = 0, x1 = 0, y1 = 1;
  while (b) {
    i64 q = a / b;
    tie(x, x1) = pair(x1, x - q * x1);
    tie(y, y1) = pair(y1, x - q * y1);
    tie(a, b) = pair(b, a - q * b);
  }
  return {a, x, y};
}
optional<pair<i64, i64>> linear_equations(i64 a0, i64 b0, i64 a1, i64 b1) {
  auto [d, x, y] = exgcd(a0, a1);
  if ((b1 - b0) % d) { return {}; }
  i64 a = a0 / d * a1, b = (i128)(b1 - b0) / d * x % (a1 / d);
  if (b < 0) { b += a1 / d; }
  b = (i128)(a0 * b + b0) % a;
  if (b < 0) { b += a; }
  return {{a, b}};
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  pair<i64, i64> ans = {1, 0};
  int n;
  cin >> n;
  for (int i = 0; i < n; i += 1) {
    i64 a, b;
    cin >> a >> b;
    ans = linear_equations(ans.first, ans.second, a, b % a).value();
  }
  cout << ans.second;
}
