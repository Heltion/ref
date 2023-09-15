// https://judge.yosupo.jp/problem/enumerate_palindromes
#include <bits/stdc++.h>
using namespace std;

vector<int> manacher(const string &s) {
  int n = s.size();
  vector<int> p(n);
  for (int i = 0, j = 0; i < n; i += 1) {
    if (j + p[j] > i) { p[i] = min(p[j * 2 - i], j + p[j] - i); }
    while (i >= p[i] and i + p[i] < n and s[i - p[i]] == s[i + p[i]]) {
      p[i] += 1;
    }
    if (i + p[i] > j + p[j]) { j = i; }
  }
  return p;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  string s;
  cin >> s;
  string t = "#";
  for (char c : s) {
    t += c;
    t += '#';
  }
  auto p = manacher(t);
  for (int i = 1; i + 1 < ssize(p); i += 1) { cout << p[i] - 1 << " "; }
}
