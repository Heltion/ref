// https://judge.yosupo.jp/problem/sum_of_floor_of_linear
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;
u64 sum_of_floor(u64 n, u64 m, u64 a, u64 b) {
  u64 ans = 0;
  while (n) {
    if (a >= m) {
      ans += a / m * n * (n - 1) / 2;
      a %= m;
    }
    if (b >= m) {
      ans += b / m * n;
      b %= m;
    }
    u64 y = a * n + b;
    if (y < m) {
      break;
    }
    tie(n, m, a, b) = tuple(y / m, a, m, y % m);
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  for (int ti = 0; ti < t; ti += 1) {
    i64 n, m, a, b;
    cin >> n >> m >> a >> b;
    cout << sum_of_floor(n, m, a, b) << "\n";
  }
}