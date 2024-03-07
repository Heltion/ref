#include <bits/stdc++.h>
using namespace std;
constexpr int sigma = 26;
struct Node {
  int link;
  array<int, sigma> next;
  Node()
      : link(0) { next.fill(0); }
};
struct AhoCorasick : vector<Node> {
  AhoCorasick()
      : vector<Node>(1) {}
  int add(const string& s, char first = 'a') {
    int p = 0;
    for (char si : s) {
      int c = si - first;
      if (not at(p).next[c]) {
        at(p).next[c] = size();
        emplace_back();
      }
      p = at(p).next[c];
    }
    return p;
  }
  void init() {
    queue<int> q;
    for (int i = 0; i < sigma; i += 1) {
      if (at(0).next[i]) {
        q.push(at(0).next[i]);
      }
    }
    while (not q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < sigma; i += 1) {
        if (at(u).next[i]) {
          at(at(u).next[i]).link = at(at(u).link).next[i];
          q.push(at(u).next[i]);
        } else {
          at(u).next[i] = at(at(u).link).next[i];
        }
      }
    }
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  while (cin >> n and n) {
    AhoCorasick ac;
    vector<string> t(n);
    vector<int> pt(n);
    for (int i = 0; i < n; i += 1) {
      cin >> t[i];
      pt[i] = ac.add(t[i]);
    }
    ac.init();
    string s;
    cin >> s;
    vector<vector<int>> g(ac.size());
    for (int i = 1; i < ssize(g); i += 1) {
      g[ac[i].link].push_back(i);
    }
    vector<int> count(ac.size());
    int p = 0;
    for (char c : s) {
      p = ac[p].next[c - 'a'];
      count[p] += 1;
    }
    auto dfs = [&](auto& dfs, int u) -> void {
      for (int v : g[u]) {
        dfs(dfs, v);
        count[u] += count[v];
      }
    };
    dfs(dfs, 0);
    int ans = -1;
    vector<string> res;
    for (int i = 0; i < n; i += 1) {
      if (count[pt[i]] > ans) {
        ans = count[pt[i]];
        res.clear();
      }
      if (count[pt[i]] == ans) {
        res.push_back(move(t[i]));
      }
    }
    cout << ans << "\n";
    for (auto& t : res) {
      cout << t << "\n";
    }
  }
}