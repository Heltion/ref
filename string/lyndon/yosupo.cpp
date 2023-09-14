// https://judge.yosupo.jp/problem/lyndon_factorization
#include <bits/stdc++.h>
using namespace std;

vector<int> lyndon_factorization(string const &s) {
  vector<int> res = {0};
  for (int i = 0, n = s.size(); i < n;) {
    int j = i + 1, k = i;
    for (; j < n and s[k] <= s[j]; j += 1) { k = s[k] < s[j] ? i : k + 1; }
    while (i <= k) { res.push_back(i += j - k); }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  for (int ai : lyndon_factorization(s)) { cout << ai << " "; }
}
