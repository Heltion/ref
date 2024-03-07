struct Line {
  mutable i64 k, b, p;
  bool operator<(const Line& rhs) const { return k < rhs.k; }
  bool operator<(const i64& x) const { return p < x; }
};
struct Lines : multiset<Line, less<>> {
  static constexpr i64 inf = numeric_limits<i64>::max();
  static i64 div(i64 a, i64 b) { return a / b - ((a ^ b) < 0 and a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) {
      return x->p = inf, false;
    }
    if (x->k == y->k) {
      x->p = x->b > y->b ? inf : -inf;
    } else {
      x->p = div(y->b - x->b, x->k - y->k);
    }
    return x->p >= y->p;
  }
  void add(i64 k, i64 b) {
    auto z = insert({k, b, 0}), y = z++, x = y;
    while (isect(y, z)) {
      z = erase(z);
    }
    if (x != begin() and isect(--x, y)) {
      isect(x, y = erase(y));
    }
    while ((y = x) != begin() and (--x)->p >= y->p) {
      isect(x, erase(y));
    }
  }
  optional<i64> get(i64 x) {
    if (empty()) {
      return {};
    }
    auto it = lower_bound(x);
    return it->k * x + it->b;
  }
};