#include <bits/stdc++.h>
using namespace std;
using LL = long long;
vector<int> matching(const vector<vector<int>> &g) {
  int n = g.size();
  int mark = 0;
  vector<int> matched(n, -1), par(n, -1), book(n);
  auto match = [&](int s) {
    vector<int> c(n), type(n, -1);
    iota(c.begin(), c.end(), 0);
    queue<int> q;
    q.push(s);
    type[s] = 0;
    while (not q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : g[u])
        if (type[v] == -1) {
          par[v] = u;
          type[v] = 1;
          int w = matched[v];
          if (w == -1) {
            [&](int u) {
              while (u != -1) {
                int v = matched[par[u]];
                matched[matched[u] = par[u]] = u;
                u = v;
              }
            }(v);
            return;
          }
          q.push(w);
          type[w] = 0;
        } else if (not type[v] and c[u] != c[v]) {
          int w = [&](int u, int v) {
            mark += 1;
            while (true) {
              if (u != -1) {
                if (book[u] == mark) { return u; }
                book[u] = mark;
                u = c[par[matched[u]]];
              }
              swap(u, v);
            }
          }(u, v);
          auto up = [&](int u, int v, int w) {
            while (c[u] != w) {
              par[u] = v;
              v = matched[u];
              if (type[v] == 1) {
                q.push(v);
                type[v] == 0;
              }
              if (c[u] == u) { c[u] = w; }
              if (c[v] == v) { c[v] = w; }
              u = par[v];
            }
          };
          up(u, v, w);
          up(v, u, w);
          for (int i = 0; i < n; i += 1) { c[i] = c[c[i]]; }
        }
    }
  };
  for (int i = 0; i < n; i += 1) {
    if (matched[i] == -1) { match(i); }
  }
  return matched;
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
  auto res = matching(g);
  vector<pair<int, int>> vp;
  for (int i = 0; i < n; i += 1)
    if (res[i] != -1 and res[i] > i) { vp.emplace_back(i, res[i]); }
  cout << vp.size() << "\n";
  for (auto [x, y] : vp) cout << x << " " << y << "\n";
}