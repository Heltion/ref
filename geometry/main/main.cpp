constexpr f64 eps = 1e-9;
int sign(f64 x) { return x < -eps ? -1 : x > eps; }
int sign(i64 x) { return x < 0 ? -1 : x > 0; }
template <typename T> struct P {
  T x, y;
  template <typename R> P(P<R> p) : x(p.x), y(p.y) {}
  P(T x = 0, T y = 0) : x(x), y(y) {}
  P operator+(P p) { return P(x + p.x, y + p.y); }
  P operator-(P p) { return P(x - p.x, y - p.y); }
  P operator*(T k) { return P(x * k, y * k); }
  T cross(P p) { return x * p.y - y * p.x; }
  T dot(P p) { return x * p.x + y * p.y; }
  T len2() { return x * x + y * y; }
  T len() { return hypot(x, y); }
};
template <typename T> struct L {
  P<T> a, b;
  template <typename R> L(L<R> l) : a(l.a), b(l.b) {}
  L(P<T> a = {}, P<T> b = {}) : a(a), b(b) {}
  P<T> v() { return b - a; }
  P<T> projection(P<T> p) { return a + v() * ((p - a).dot(v()) / v().len2()); }
  P<T> reflection(P<T> p) { return projection(p) * 2 - p; }
  int left(P<T> p) { return sign((v()).cross(p - a)); }
  // Returns (p,q) s.t. a+v()*p/q on the line l if l not in parallel.
  optional<pair<T, T>> intersection(L l) {
    T q = v().cross(l.v());
    if (q == 0) { return {}; }
    T p = (l.a - a).cross(l.v());
    return q < 0 ? pair(-p, -q) : pair(p, q);
  }
  bool is_intersection(L l) {
    auto pq = intersection(l);
    if (not pq) { return false; }
    auto [p, q] = pq.value();
    return p >= 0 and p <= q;
  }
  T distance(P<T> p) {
    if (sign((p - a).dot(v())) <= 0) { return (p - a).len(); }
    if (sign((p - b).dot(v())) >= 0) { return (p - b).len(); }
    return abs((p - a).cross(p - b)) / v().len();
  }
  T distance(L l) {
    if (is_intersection(l) and l.is_intersection(*this)) { return 0; }
    return min({distance(l.a), distance(l.b), l.distance(a), l.distance(b)});
  }
};
template <typename T> struct H {
  int n;
  vector<P<T>> p;
  H(int n) : n(n), p(n) {}
  T area2() {
    T res = 0;
    for (int i = 0; i < n; i += 1) { res += p[i].cross(p[(i + 1) % n]); }
    return res;
  }
  bool is_convex() {
    for (int i = 0; i < n; i += 1) {
      auto a = p[i], b = p[(i + 1) % n], c = p[(i + 2) % n];
      if (sign((b - a).cross(c - a)) == -1) { return false; };
    }
    return true;
  }
  optional<int> winding(P<T> q) {
    int res = 0;
    for (int i = 0; i < n; i += 1) {
      auto a = p[i], b = p[(i + 1) % n];
      if (sign((q - a).cross(q - b)) == 0 and sign((q - a).dot(q - b)) <= 0) {
        return {};
      }
      L l(a, b);
      int s = sign(a.y - b.y);
      if (s == -1 and l.left(q) <= 0) { continue; }
      if (s == 0) { continue; }
      if (s == 1 and l.left(q) >= 0) { continue; }
      if (sign(a.y - q.y) == -1 and sign(b.y - q.y) >= 0) { res += 1; }
      if (sign(a.y - q.y) >= 0 and sign(b.y - q.y) == -1) { res -= 1; }
    }
    return res;
  }
};