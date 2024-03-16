// https://judge.yosupo.jp/problem/runenumerate
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
vector<int> lyndon_factorization(string const &s) {
  int n = s.size();
  vector<int> res = {0};
  for (int i = 0; i < n;) {
    int j = i + 1, k = i;
    for (; j < n and s[k] <= s[j]; j += 1) k = s[k] < s[j] ? i : k + 1;
    while (i <= k) res.push_back(i += j - k);
  }
  return res;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  string s;
  cin >> s;
  for (int i : lyndon_factorization(s)) cout << i << " ";
}