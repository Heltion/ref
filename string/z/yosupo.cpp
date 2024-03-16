// https://judge.yosupo.jp/problem/zalgorithm
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
vector<int> fz(const string& s) {
  int n = s.size();
  vector<int> z(n);
  for (int i = 1, j = 0; i < n; i += 1) {
    z[i] = max(min(j + z[j] - i, z[i - j]), 0);
    while (s[z[i]] == s[i + z[i]]) z[i] += 1;
    if (i + z[i] > j + z[j]) j = i;
  }
  z[0] = n;
  return z;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  string s;
  cin >> s;
  for (int zi : fz(s)) cout << zi << " ";
}