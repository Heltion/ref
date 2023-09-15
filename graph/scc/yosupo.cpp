// https://judge.yosupo.jp/problem/scc
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>>
strongly_connected_components(const vector<vector<int>> &g) {
  int n = g.size();
  vector<bool> done(n);
  vector<int> pos(n, -1), stack;
  vector<vector<int>> res;
  function<int(int)> dfs = [&](int u) {
    int low = pos[u] = stack.size();
    stack.push_back(u);
    for (int v : g[u]) {
      if (not done[v]) { low = min(low, ~pos[v] ? pos[v] : dfs(v)); }
    }
    if (low == pos[u]) {
      res.emplace_back(stack.begin() + low, stack.end());
      for (int v : res.back()) { done[v] = true; }
      stack.resize(low);
    }
    return low;
  };
  for (int i = 0; i < n; i += 1) {
    if (not done[i]) { dfs(i); }
  }
  ranges::reverse(res);
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
  }
  auto scc = strongly_connected_components(g);
  cout << scc.size() << "\n";
  for (const auto &cc : scc) {
    cout << cc.size();
    for (int u : cc) { cout << " " << u; }
    cout << "\n";
  }
}