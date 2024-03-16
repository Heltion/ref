// https://www.luogu.com.cn/problem/P5357
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
struct AhoCorasick {
  struct Node : array<int, sigma> {
    int link;
    Node() : link(0) { this->fill(0); }
  };
  vector<Node> nodes;
  AhoCorasick() : nodes(1) {}
  int insert(const string& s) {
    int p = 0;
    for (char c : s) {
      int ci = c - first;
      if (not nodes[p][ci]) {
        nodes[p][ci] = nodes.size();
        nodes.emplace_back();
      }
      p = nodes[p][ci];
    }
    return p;
  }
  void init() {
    queue<int> q;
    q.push(0);
    while (not q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < sigma; i += 1) {
        int &v = nodes[u][i], w = nodes[nodes[u].link][i];
        if (not v) {
          v = w;
          continue;
        }
        nodes[v].link = u ? w : 0;
        q.push(v);
      }
    }
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n;
  cin >> n;
  AhoCorasick ac;
  vector<int> end(n);
  for (int i = 0; i < n; i += 1) {
    string t;
    cin >> t;
    end[i] = ac.insert(t);
  }
  ac.init();
  auto& nodes = ac.nodes;
  int m = nodes.size();
  vector<vector<int>> g(m);
  vector<int> count(m);
  for (int i = 1; i < m; i += 1) g[nodes[i].link].push_back(i);
  string s;
  cin >> s;
  int p = 0;
  for (char c : s) {
    p = nodes[p][c - 'a'];
    count[p] += 1;
  }
  auto dfs = [&](auto& dfs, int u) -> void {
    for (int v : g[u]) {
      dfs(dfs, v);
      count[u] += count[v];
    }
  };
  dfs(dfs, 0);
  for (int i : end) cout << count[i] << "\n";
}