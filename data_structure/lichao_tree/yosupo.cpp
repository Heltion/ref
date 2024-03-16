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
struct Line {
  i64 k, b;
  i64 operator()(i64 x) const { return k * x + b; }
};
template <i64 L, i64 R>
struct Segments {
  struct Node {
    optional<Line> s;
    Node *l, *r;
  };
  Node *root;
  Segments() : root(nullptr) {}
  void add(i64 l, i64 r, i64 k, i64 b) {
    auto rec = [&](auto &rec, Node *&p, i64 tl, i64 tr, Line s) -> void {
      if (p == nullptr) p = new Node();
      i64 tm = midpoint(tl, tr);
      if (tl >= l and tr <= r) {
        if (not p->s) return p->s = s, void();
        auto t = p->s.value();
        if (t(tl) >= s(tl)) {
          if (t(tr) >= s(tr)) return;
          if (t(tm) >= s(tm)) return rec(rec, p->r, tm + 1, tr, s);
          return p->s = s, rec(rec, p->l, tl, tm, t);
        }
        if (t(tr) <= s(tr)) return p->s = s, void();
        if (t(tm) <= s(tm)) return p->s = s, rec(rec, p->r, tm + 1, tr, t);
        return rec(rec, p->l, tl, tm, s);
      }
      if (l <= tm) rec(rec, p->l, tl, tm, s);
      if (r > tm) rec(rec, p->r, tm + 1, tr, s);
    };
    rec(rec, root, L, R, {k, b});
  }
  optional<i64> get(i64 x) {
    optional<i64> res = {};
    auto rec = [&](auto &rec, Node *p, i64 tl, i64 tr) -> void {
      if (p == nullptr) return;
      i64 tm = midpoint(tl, tr);
      if (p->s) {
        i64 y = p->s.value()(x);
        if (not res or res.value() < y) res = y;
      }
      if (x <= tm)
        rec(rec, p->l, tl, tm);
      else
        rec(rec, p->r, tm + 1, tr);
    };
    rec(rec, root, L, R);
    return res;
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, q;
  cin >> n >> q;
  Segments<-1000000000, 1000000000> segments;
  for (int i = 0; i < n; i += 1) {
    i64 l, r, a, b;
    cin >> l >> r >> a >> b;
    segments.add(l, r - 1, -a, -b);
  }
  for (int qi = 0, qt; qi < q; qi += 1) {
    cin >> qt;
    if (qt == 0) {
      i64 l, r, a, b;
      cin >> l >> r >> a >> b;
      segments.add(l, r - 1, -a, -b);
    }
    if (qt == 1) {
      i64 x;
      cin >> x;
      auto ans = segments.get(x);
      if (ans)
        cout << -ans.value() << "\n";
      else
        cout << "INFINITY\n";
    }
  }
}
