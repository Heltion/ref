#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr i64 mod = 998244353;
constexpr i64 g = 3;
i64 power(i64 a, i64 r) {
  i64 res = 1;
  for (; r; r >>= 1, a = a * a % mod) {
    if (r & 1) { res = res * a % mod; }
  }
  return res;
}
void fft(vector<i64> &a, bool inverse) {
  int n = a.size();
  vector<int> r(n);
  for (int i = 0; i < n; i += 1) { r[i] = r[i / 2] / 2 | (i % 2 ? n / 2 : 0); }
  for (int i = 0; i < n; i += 1) {
    if (i < r[i]) { swap(a[i], a[r[i]]); }
  }
  for (int m = 1; m < n; m *= 2) {
    i64 wn = power(inverse ? power(g, mod - 2) : g, (mod - 1) / m / 2);
    for (int i = 0; i < n; i += m * 2) {
      i64 w = 1;
      for (int j = 0; j < m; j += 1, w = w * wn % mod) {
        auto &x = a[i + j + m], &y = a[i + j], t = w * x % mod;
        tie(x, y) = pair((y + mod - t) % mod, (y + t) % mod);
      }
    }
  }
  if (inverse) {
    i64 inv = power(n, mod - 2);
    for (auto &ai : a) { ai = ai * inv % mod; }
  }
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  unsigned n, m;
  cin >> n >> m;
  vector<i64> a(n), b(m);
  for (i64 &ai : a) { cin >> ai; }
  for (i64 &bi : b) { cin >> bi; }
  int k = bit_ceil(n + m - 1);
  a.resize(k);
  fft(a, false);
  b.resize(k);
  fft(b, false);
  for (int i = 0; i < k; i += 1) { a[i] = a[i] * b[i] % mod; }
  fft(a, true);
  a.resize(n + m - 1);
  for (i64 ai : a) { cout << ai << " "; }
}
