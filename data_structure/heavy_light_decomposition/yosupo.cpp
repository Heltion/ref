// https://judge.yosupo.jp/problem/vertex_set_path_composite
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
template <class T, auto bop, auto e>
struct SegmentTree {
  int n;
  vector<T> s;
  SegmentTree(int n) : n(n), s(n * 2, e()) {}
  void set(int i, T v) {
    for (s[i += n] = v; i /= 2;) s[i] = bop(s[i * 2], s[i * 2 + 1]);
  }
  T product(int l, int r) {
    T rl = e(), rr = e();
    for (l += n, r += n + 1; l != r; l /= 2, r /= 2) {
      if (l % 2) rl = bop(rl, s[l++]);
      if (r % 2) rr = bop(s[--r], rr);
    }
    return bop(rl, rr);
  }
};
struct HeavyLigthDecomposition {
  vector<int> p, pos, top;
  HeavyLigthDecomposition(const vector<vector<int>>& adj) {
    int n = adj.size(), m = 0;
    p.resize(n, -1);
    pos.resize(n);
    top.resize(n);
    vector<int> size(n, 1), h(n, -1);
    auto dfs0 = [&](auto& dfs, int u) -> void {
      for (int v : adj[u]) {
        if (v == p[u]) continue;
        p[v] = u;
        dfs(dfs, v);
        size[u] += size[v];
        if (h[u] == -1 or size[h[u]] < size[v]) h[u] = v;
      }
    };
    dfs0(dfs0, 0);
    auto dfs1 = [&](auto& dfs, int u) -> void {
      pos[u] = m++;
      if (~h[u]) {
        top[h[u]] = top[u];
        dfs(dfs, h[u]);
      }
      for (int v : adj[u]) {
        if (v == p[u] or v == h[u]) continue;
        dfs(dfs, top[v] = v);
      }
    };
    dfs1(dfs1, top[0] = 0);
  }
  vector<tuple<int, int, bool>> dec(int u, int v) {
    vector<tuple<int, int, bool>> pu, pv;
    while (top[u] != top[v]) {
      if (pos[u] > pos[v]) {
        pu.emplace_back(pos[top[u]], pos[u], true);
        u = p[top[u]];
      } else {
        pv.emplace_back(pos[top[v]], pos[v], false);
        v = p[top[v]];
      }
    }
    if (pos[u] <= pos[v])
      pv.emplace_back(pos[u], pos[v], false);
    else
      pu.emplace_back(pos[v], pos[u], true);
    ranges::reverse(pv);
    pu.insert(pu.end(), pv.begin(), pv.end());
    return pu;
  }
};
constexpr i64 mod = 998244353;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, q;
  cin >> n >> q;
  vector<pair<i64, i64>> p(n);
  for (auto& [x, y] : p) cin >> x >> y;
  vector<vector<int>> adj(n);
  for (int i = 1, a, b; i < n; i += 1) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  HeavyLigthDecomposition hld(adj);
  using T = pair<i64, i64>;
  auto bop = [](T t0, T t1) {
    auto [a0, b0] = t0;
    auto [a1, b1] = t1;
    return pair(a0 * a1 % mod, (b0 * a1 + b1) % mod);
  };
  auto e = [] { return pair(1, 0); };
  SegmentTree<T, bop, e> st(n);
  SegmentTree<T,
              [](T t0, T t1) {
                auto [a0, b0] = t0;
                auto [a1, b1] = t1;
                return pair(a0 * a1 % mod, (b1 * a0 + b0) % mod);
              },
              e>
      rt(n);
  for (int i = 0; i < n; i += 1) {
    st.set(hld.pos[i], p[i]);
    rt.set(hld.pos[i], p[i]);
  }
  for (int qi = 0, qt; qi < q; qi += 1) {
    cin >> qt;
    if (qt == 0) {
      int p, c, d;
      cin >> p >> c >> d;
      st.set(hld.pos[p], pair(c, d));
      rt.set(hld.pos[p], pair(c, d));
    }
    if (qt == 1) {
      int u, v, x;
      cin >> u >> v >> x;
      T res = e();
      for (auto [u, v, r] : hld.dec(u, v)) res = bop(res, r ? rt.product(u, v) : st.product(u, v));
      auto [a, b] = res;
      cout << (a * x + b) % mod << "\n";
    }
  }
}