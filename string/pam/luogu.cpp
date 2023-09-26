#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr int sigma = 26;
struct Node {
  int sum, len, link;
  array<int, sigma> next;
  Node(int len) : len(len) {
    sum = link = 0;
    next.fill(0);
  }
};
struct PalindromicTree : vector<Node> {
  int last;
  vector<int> s;
  PalindromicTree() : last(0) {
    emplace_back(0);
    emplace_back(-1);
    at(0).link = 1;
  }
  int get_link(int u, int i) {
    while (i < at(u).len + 1 or s[i - at(u).len - 1] != s[i]) u = at(u).link;
    return u;
  }
  void extend(int i) {
    int cur = get_link(last, i);
    if (not at(cur).next[s[i]]) {
      int now = size();
      emplace_back(at(cur).len + 2);
      back().link = at(get_link(at(cur).link, i)).next[s[i]];
      back().sum = at(back().link).sum + 1;
      at(cur).next[s[i]] = now;
    }
    last = at(cur).next[s[i]];
  }
};
int main() {
  cin.sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin >> s;
  PalindromicTree pt;
  int ans = 0;
  for (int i = 0; i < (int)s.size(); i += 1) {
    pt.s.push_back((ans + s[i] - 'a') % 26);
    pt.extend(i);
    ans = pt[pt.last].sum;
    cout << ans << " ";
  }
  return 0;
}