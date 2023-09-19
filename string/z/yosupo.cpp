// https://judge.yosupo.jp/problem/zalgorithm

#include <bits/stdc++.h>
using namespace std;

vector<int> fz(const string &s) {
  int n = s.size();
  vector<int> z(n);
  for (int i = 1, j = 0; i < n; i += 1) {
    z[i] = max(min(z[i - j], j + z[j] - i), 0);
    while (i + z[i] < n and s[i + z[i]] == s[z[i]]) { z[i] += 1; }
    if (i + z[i] > j + z[j]) { j = i; }
  }
  return z;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  string s;
  cin >> s;
  auto z = f(s);
  z[0] = s.size();
  for (int zi : z) { cout << zi << " "; }
}
