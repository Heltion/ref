// https://judge.yosupo.jp/problem/enumerate_palindromes
#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "debug.hpp"
#else
#define debug(...) void(0)
#endif
using i64 = int64_t;
using u64 = uint64_t;
using f64 = double_t;
vector<int> fp(const string& s) {
  int n = s.size();
  vector<int> p(n * 2 - 1);
  for (int i = 0, j = 0; i < n * 2 - 1; i += 1) {
    if (j + p[j] > i) p[i] = min(j + p[j] - i, p[2 * j - i]);
    while (i >= p[i] and i + p[i] <= 2 * n and ((i - p[i]) % 2 == 0 or s[(i - p[i]) / 2] == s[(i + p[i] + 1) / 2])) p[i] += 1;
    if (i + p[i] > j + p[j]) j = i;
  }
  return p;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  string s;
  cin >> s;
  for (int pi : fp(s)) cout << pi << " ";
}