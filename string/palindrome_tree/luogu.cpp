// https://www.luogu.com.cn/problem/P6139
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
template <int sigma = 26, char first = 'a'>
struct PalindromeTree {
  struct Node : array<int, sigma> {
    int len, link, count;
    Node(int len) : len(len) {
      link = count = 0;
      this->fill(0);
    }
  };
  int last;
  string s;
  vector<Node> nodes;
  PalindromeTree() : last(0), nodes({0, -1}) { nodes[0].link = 1; }
  int get_link(int u, int i) {
    while (i < nodes[u].len + 1 or s[i - nodes[u].len - 1] != s[i]) u = nodes[u].link;
    return u;
  }
  void extend(char c) {
    int i = s.size(), ci = c - first;
    s.push_back(c);
    int cur = get_link(last, i);
    if (not nodes[cur][ci]) {
      int now = nodes.size();
      nodes.push_back(nodes[cur].len + 2);
      nodes.back().link = nodes[get_link(nodes[cur].link, i)][ci];
      nodes.back().count = nodes[nodes.back().link].count + 1;
      nodes[cur][ci] = now;
    }
    last = nodes[cur][ci];
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  string s;
  cin >> s;
  int ans = 0;
  PalindromeTree pam;
  for (int i = 0; i < (int)s.size(); i += 1) {
    char c = (ans + s[i] - 'a') % 26 + 'a';
    pam.extend(c);
    ans = pam.nodes[pam.last].count;
    cout << ans << " ";
  }
}