// https://www.luogu.com.cn/problem/P5829

#include <bits/stdc++.h>
using namespace std;

vector<int> fborder(const string &s) {
  int n = s.size();
  vector<int> res(n);
  for (int i = 1; i < n; i += 1) {
    int &j = res[i] = res[i - 1];
    while (j and s[i] != s[j]) { j = res[j - 1]; }
    j += s[i] == s[j];
  }
  return res;
}

struct SparseTable {
  vector<vector<int>> table;
  void init(const vector<int> &a) {
    int n = a.size(), h = bit_width(a.size());
    table.resize(h);
    table[0] = a;
    for (int i = 1; i < h; i += 1) {
      table[i].resize(n - (1 << i) + 1);
      for (int j = 0; j + (1 << i) <= n; j += 1) {
        table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int query(int l, int r) {
    int h = bit_width(unsigned(r - l)) - 1;
    return min(table[h][l], table[h][r - (1 << h)]);
  }
};

struct LeastCommonAncestor {
  SparseTable st;
  vector<int> p, time, a, par;
  LeastCommonAncestor(const vector<vector<int>> &g, int root) {
    int n = g.size();
    time.resize(n, -1);
    par.resize(n, -1);
    function<void(int)> dfs = [&](int u) {
      time[u] = p.size();
      p.push_back(u);
      for (int v : g[u]) {
        if (time[v] == -1) {
          par[v] = u;
          dfs(v);
        }
      }
    };
    dfs(root);
    a.resize(n);
    for (int i = 1; i < n; i += 1) { a[i] = time[par[p[i]]]; }
    st.init(a);
  }
  int query(int u, int v) {
    if (u == v) { return u; }
    if (time[u] > time[v]) { swap(u, v); }
    return p[st.query(time[u] + 1, time[v] + 1)];
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  string s;
  cin >> s;
  auto border = fborder(s);
  int n = s.size();
  vector<vector<int>> g(n + 1);
  for (int i = 0; i < n; i += 1) {
    g[i + 1].push_back(border[i]);
    g[border[i]].push_back(i + 1);
  }
  LeastCommonAncestor lca(g, 0);
  int q;
  cin >> q;
  for (int qi = 0; qi < q; qi += 1) {
    int u, v;
    cin >> u >> v;
    cout << lca.query(border[u - 1], border[v - 1]) << "\n";
  }
}