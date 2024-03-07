struct Mv {
  static constexpr i64 inf = numeric_limits<i64>::max() / 2;
  i64 mv, smv, cmv, tmv;
  bool less;
  i64 def() { return less ? inf : -inf; }
  i64 mmv(i64 x, i64 y) { return less ? min(x, y) : max(x, y); }
  Mv(i64 x, bool less) : less(less) {
    mv = x;
    smv = tmv = def();
    cmv = 1;
  }
  void up(const Mv& ls, const Mv& rs) {
    mv = mmv(ls.mv, rs.mv);
    smv = mmv(ls.mv == mv ? ls.smv : ls.mv, rs.mv == mv ? rs.smv : rs.mv);
    cmv = (ls.mv == mv ? ls.cmv : 0) + (rs.mv == mv ? rs.cmv : 0);
  }
  void add(i64 x) {
    mv += x;
    if (smv != def()) {
      smv += x;
    }
    if (tmv != def()) {
      tmv += x;
    }
  }
};
struct Node {
  Mv mn, mx;
  i64 sum, tsum;
  Node *ls, *rs;
  Node(i64 x = 0) : sum(x), tsum(0), mn(x, true), mx(x, false) { ls = rs = nullptr; }
  void up() {
    sum = ls->sum + rs->sum;
    mx.up(ls->mx, rs->mx);
    mn.up(ls->mn, rs->mn);
  }
  void down(int tl, int tr) {
    if (tsum) {
      int tm = midpoint(tl, tr);
      ls->add(tl, tm, tsum);
      rs->add(tm, tr, tsum);
      tsum = 0;
    }
    if (mn.tmv != mn.def()) {
      ls->ch(mn.tmv, true);
      rs->ch(mn.tmv, true);
      mn.tmv = mn.def();
    }
    if (mx.tmv != mx.def()) {
      ls->ch(mx.tmv, false);
      rs->ch(mx.tmv, false);
      mx.tmv = mx.def();
    }
  }
  bool cmp(i64 x, i64 y, bool less) { return less ? x < y : x > y; }
  void add(int tl, int tr, i64 x) {
    sum += (tr - tl) * x;
    tsum += x;
    mx.add(x);
    mn.add(x);
  }
  void ch(i64 x, bool less) {
    auto &lhs = less ? mn : mx, &rhs = less ? mx : mn;
    if (not cmp(x, rhs.mv, less)) {
      return;
    }
    sum += (x - rhs.mv) * rhs.cmv;
    if (lhs.smv == rhs.mv) {
      lhs.smv = x;
    }
    if (lhs.mv == rhs.mv) {
      lhs.mv = x;
    }
    if (cmp(x, rhs.tmv, less)) {
      rhs.tmv = x;
    }
    rhs.mv = lhs.tmv = x;
  }
  void add(int tl, int tr, int l, int r, i64 x) {
    if (tl >= l and tr <= r) {
      return add(tl, tr, x);
    }
    down(tl, tr);
    int tm = midpoint(tl, tr);
    if (l < tm) {
      ls->add(tl, tm, l, r, x);
    }
    if (r > tm) {
      rs->add(tm, tr, l, r, x);
    }
    up();
  }
  void ch(int tl, int tr, int l, int r, i64 x, bool less) {
    auto &lhs = less ? mn : mx, &rhs = less ? mx : mn;
    if (not cmp(x, rhs.mv, less)) {
      return;
    }
    if (tl >= l and tr <= r and cmp(rhs.smv, x, less)) {
      return ch(x, less);
    }
    down(tl, tr);
    int tm = midpoint(tl, tr);
    if (l < tm) {
      ls->ch(tl, tm, l, r, x, less);
    }
    if (r > tm) {
      rs->ch(tm, tr, l, r, x, less);
    }
    up();
  }
  i64 get(int tl, int tr, int l, int r) {
    if (tl >= l and tr <= r) {
      return sum;
    }
    down(tl, tr);
    i64 res = 0;
    int tm = midpoint(tl, tr);
    if (l < tm) {
      res += ls->get(tl, tm, l, r);
    }
    if (r > tm) {
      res += rs->get(tm, tr, l, r);
    }
    return res;
  }
};