#include <bits/stdc++.h>
using namespace std;
constexpr int sigma = 26;
struct Node {
  int link, len;
  array<int, sigma> next;
  Node()
      : link(-1), len(0) { next.fill(-1); }
};
struct SuffixAutomaton : vector<Node> {
  SuffixAutomaton()
      : vector<Node>(1) {}
  int extend(int p, int c) {
    if (~at(p).next[c]) {
      // For online multiple strings.
      int q = at(p).next[c];
      if (at(p).len + 1 == at(q).len) {
        return q;
      }
      int clone = size();
      push_back(at(q));
      back().len = at(p).len + 1;
      while (~p and at(p).next[c] == q) {
        at(p).next[c] = clone;
        p = at(p).link;
      }
      at(q).link = clone;
      return clone;
    }
    int cur = size();
    emplace_back();
    back().len = at(p).len + 1;
    while (~p and at(p).next[c] == -1) {
      at(p).next[c] = cur;
      p = at(p).link;
    }
    if (~p) {
      int q = at(p).next[c];
      if (at(p).len + 1 == at(q).len) {
        back().link = q;
      } else {
        int clone = size();
        push_back(at(q));
        back().len = at(p).len + 1;
        while (~p and at(p).next[c] == q) {
          at(p).next[c] = clone;
          p = at(p).link;
        }
        at(q).link = at(cur).link = clone;
      }
    } else {
      back().link = 0;
    }
    return cur;
  }
};
using i64 = int64_t;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  SuffixAutomaton sam;
  for (int i = 0; i < n; i += 1) {
    string s;
    cin >> s;
    int p = 0;
    for (char c : s) {
      p = sam.extend(p, c - 'a');
    }
  }
  i64 ans = 0;
  for (int i = 1; i < sam.size(); i += 1) {
    ans += sam[i].len - sam[sam[i].link].len;
  }
  cout << ans << "\n"
       << sam.size() << "\n";
}