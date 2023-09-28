#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Segment {
  i64 k, b;
  i64 get(i64 x) { return k * x + b; }
};
struct Segments {
  struct Node {
    optional<Segment> s;
    Node *l, *r;
  };
  i64 tl, tr;
  Node *root;
  Segments(i64 tl, i64 tr) : tl(tl), tr(tr), root(nullptr) {}
  void add(i64 l, i64 r, i64 k, i64 b) {
    function<void(Node *&, i64, i64, Segment)> rec = [&](Node *&p, i64 tl,
                                                         i64 tr, Segment s) {
      if (p == nullptr) { p = new Node(); }
      i64 tm = midpoint(tl, tr);
      if (tl >= l and tr <= r) {
        if (not p->s) {
          p->s = s;
          return;
        }
        auto t = p->s.value();
        if (t.get(tl) >= s.get(tl)) {
          if (t.get(tr) >= s.get(tr)) { return; }
          if (t.get(tm) >= s.get(tm)) { return rec(p->r, tm + 1, tr, s); }
          p->s = s;
          return rec(p->l, tl, tm, t);
        }
        if (t.get(tr) <= s.get(tr)) {
          p->s = s;
          return;
        }
        if (t.get(tm) <= s.get(tm)) {
          p->s = s;
          return rec(p->r, tm + 1, tr, t);
        }
        return rec(p->l, tl, tm, s);
      }
      if (l <= tm) { rec(p->l, tl, tm, s); }
      if (r > tm) { rec(p->r, tm + 1, tr, s); }
    };
    rec(root, tl, tr, {k, b});
  }
  optional<i64> get(i64 x) {
    optional<i64> res = {};
    function<void(Node *, i64, i64)> rec = [&](Node *p, i64 tl, i64 tr) {
      if (p == nullptr) { return; }
      i64 tm = midpoint(tl, tr);
      if (p->s) {
        i64 y = p->s.value().get(x);
        if (not res or res.value() < y) { res = y; }
      }
      if (x <= tm) {
        rec(p->l, tl, tm);
      } else {
        rec(p->r, tm + 1, tr);
      }
    };
    rec(root, tl, tr);
    return res;
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  Segments segments(-1000000000, 1000000000);
  for (int i = 0; i < n; i += 1) {
    i64 l, r, a, b;
    cin >> l >> r >> a >> b;
    segments.add(l, r - 1, -a, -b);
  }
  for (int i = 0, t; i < q; i += 1) {
    cin >> t;
    if (t == 0) {
      i64 l, r, a, b;
      cin >> l >> r >> a >> b;
      segments.add(l, r - 1, -a, -b);
    } else {
      i64 x;
      cin >> x;
      auto ans = segments.get(x);
      if (ans) {
        cout << -ans.value() << "\n";
      } else {
        cout << "INFINITY\n";
      }
    }
  }
}
