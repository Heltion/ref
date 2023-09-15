// https://judge.yosupo.jp/problem/dominatortree
#include <bits/stdc++.h>
using namespace std;

vector<int> dominator(const vector<vector<int>> &g, int s) {
  int n = g.size();
  vector<int> pos(n, -1), p, label(n), dom(n), sdom(n), dsu(n), par(n);
  vector<vector<int>> rg(n), bucket(n);
  function<void(int)> dfs = [&](int u) {
    int t = p.size();
    p.push_back(u);
    label[t] = sdom[t] = dsu[t] = pos[u] = t;
    for (int v : g[u]) {
      if (pos[v] == -1) {
        dfs(v);
        par[pos[v]] = t;
      }
      rg[pos[v]].push_back(t);
    }
  };
  function<int(int, int)> find = [&](int u, int x) {
    if (u == dsu[u]) { return x ? -1 : u; }
    int v = find(dsu[u], x + 1);
    if (v < 0) { return u; }
    if (sdom[label[dsu[u]]] < sdom[label[u]]) { label[u] = label[dsu[u]]; }
    dsu[u] = v;
    return x ? v : label[u];
  };
  dfs(s);
  iota(dom.begin(), dom.end(), 0);
  for (int i = ssize(p) - 1; i >= 0; i -= 1) {
    for (int j : rg[i]) { sdom[i] = min(sdom[i], sdom[find(j, 0)]); }
    if (i) { bucket[sdom[i]].push_back(i); }
    for (int k : bucket[i]) {
      int j = find(k, 0);
      dom[k] = sdom[j] == sdom[k] ? sdom[j] : j;
    }
    if (i > 1) { dsu[i] = par[i]; }
  }
  for (int i = 1; i < ssize(p); i += 1) {
    if (dom[i] != sdom[i]) { dom[i] = dom[dom[i]]; }
  }
  vector<int> res(n, -1);
  res[s] = s;
  for (int i = 1; i < ssize(p); i += 1) { res[p[i]] = p[dom[i]]; }
  return res;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, s;
  cin >> n >> m >> s;
  vector<vector<int>> g(n);
  for (int i = 0, u, v; i < m; i += 1) {
    cin >> u >> v;
    g[u].push_back(v);
  }
  for (int pi : dominator(g, s)) { cout << pi << " "; }
}
