// https://judge.yosupo.jp/problem/two_edge_connected_components
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> bcc(const vector<vector<int>> &g) {
  int n = g.size();
  vector<int> pos(n, -1), stack;
  vector<vector<int>> res;
  function<int(int, int)> dfs = [&](int u, int p) {
    int low = pos[u] = stack.size(), pc = 0;
    stack.push_back(u);
    for (int v : g[u]) {
      if (~pos[v]) {
        if (v != p or pc++) { low = min(low, pos[v]); }
      } else {
        low = min(low, dfs(v, u));
      }
    }
    if (low == pos[u]) {
      res.emplace_back(stack.begin() + low, stack.end());
      stack.resize(low);
    }
    return low;
  };
  for (int i = 0; i < n; i += 1) {
    if (pos[i] == -1) { dfs(i, -1); }
  }
  return res;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0, u, v; i < m; i += 1) {
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  auto bccs = bcc(g);
  cout << bccs.size() << "\n";
  for (const auto &bcc : bccs) {
    cout << bcc.size();
    for (int u : bcc) { cout << " " << u; }
    cout << "\n";
  }
}