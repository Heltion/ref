// https://judge.yosupo.jp/problem/point_set_range_composite
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) void(0)
#endif
using i64 = int64_t;
template <class T, auto f, auto e>
  requires is_constructible_v<function<T(T, T)>, decltype(f)> and is_constructible_v<function<T()>, decltype(e)>
struct SegmentTree {
  int n;
  vector<T> s;
  SegmentTree(int n) : n(n), s(n * 2, e()) {}
  void set(int i, T v) {
    for (s[i += n] = v; i /= 2;) s[i] = f(s[i * 2], s[i * 2 + 1]);
  }
  /// Returns the product of elements in [l, r).
  T product(int l, int r) {
    T rl = e(), rr = e();
    for (l += n, r += n; l != r; l /= 2, r /= 2) {
      if (l % 2) rl = f(rl, s[l++]);
      if (r % 2) rr = f(s[r -= 1], rr);
    }
    return f(rl, rr);
  }
};
constexpr i64 mod = 998244353;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, q;
  cin >> n >> q;
  using T = pair<i64, i64>;
  SegmentTree<T,
              [](T t0, T t1) {
                auto [a0, b0] = t0;
                auto [a1, b1] = t1;
                return pair(a0 * a1 % mod, (b0 * a1 + b1) % mod);
              },
              []() { return pair(1, 0); }>
      st(n);
  for (int i = 0, a, b; i < n; i += 1) {
    cin >> a >> b;
    st.set(i, pair(a, b));
  }
  for (int qi = 0, t; qi < q; qi += 1) {
    cin >> t;
    if (t == 0) {
      int p, c, d;
      cin >> p >> c >> d;
      st.set(p, pair(c, d));
    }
    if (t == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      auto [a, b] = st.product(l, r);
      cout << (a * x + b) % mod << "\n";
    }
  }
}