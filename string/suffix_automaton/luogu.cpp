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
struct SuffixAutomaton {
  struct Node : array<int, sigma> {
    int link, len;
    Node() : link(-1), len(0) { this->fill(-1); }
  };
  vector<Node> nodes;
  SuffixAutomaton() : nodes(1) {}
  int extend(int p, char c) {
    int ci = c - first;
    if (~nodes[p][ci]) {
      int q = nodes[p][ci];
      if (nodes[p].len + 1 == nodes[q].len) return q;
      int clone = nodes.size();
      nodes.push_back(nodes[q]);
      nodes.back().len = nodes[p].len + 1;
      while (~p and nodes[p][ci] == q) {
        nodes[p][ci] = clone;
        p = nodes[p].link;
      }
      nodes[q].link = clone;
      return clone;
    }
    int cur = nodes.size();
    nodes.emplace_back();
    nodes.back().len = nodes[p].len + 1;
    while (~p and nodes[p][ci] == -1) {
      nodes[p][ci] = cur;
      p = nodes[p].link;
    }
    if (~p) {
      int q = nodes[p][ci];
      if (nodes[p].len + 1 == nodes[q].len)
        nodes.back().link = q;
      else {
        int clone = nodes.size();
        nodes.push_back(nodes[q]);
        nodes.back().len = nodes[p].len + 1;
        while (~p and nodes[p][ci] == q) {
          nodes[p][ci] = clone;
          p = nodes[p].link;
        }
        nodes[q].link = nodes[cur].link = clone;
      }
    } else
      nodes.back().link = 0;
    return cur;
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n;
  cin >> n;
  SuffixAutomaton sam;
  for (int i = 0; i < n; i += 1) {
    string s;
    cin >> s;
    int p = 0;
    for (char c : s) p = sam.extend(p, c);
  }
  auto &nodes = sam.nodes;
  i64 ans = 0;
  for (int i = 1; i < ssize(nodes); i += 1) ans += nodes[i].len - nodes[nodes[i].link].len;
  cout << ans << "\n" << nodes.size();
}