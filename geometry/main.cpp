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
template <typename T>
T eps = 0;
template <>
f64 eps<f64> = 1e-9;
template <typename T>
int sign(T x) {
  return x < -eps<T> ? -1 : x > eps<T>;
}
template <typename T>
struct P {
  T x, y;
  explicit P(T x = 0, T y = 0) : x(x), y(y) {}
  P operator*(T k) { return P(x * k, y * k); }
  P operator+(P p) { return P(x + p.x, y + p.y); }
  P operator-(P p) { return P(x - p.x, y - p.y); }
  P operator-() { return P(-x, -y); }
  T len2() { return x * x + y * y; }
  T cross(P p) { return x * p.y - y * p.x; }
  T dot(P p) { return x * p.x + y * p.y; }
  bool operator==(P p) { return sign(x - p.x) == 0 and sign(y - p.y) == 0; }
  int arg() { return y < 0 or (y == 0 and x > 0) ? -1 : x or y; }
  P rotate90() { return P(-y, x); }
};
template <typename T>
bool argument(P<T> lhs, P<T> rhs) {
  if (lhs.arg() != rhs.arg()) return lhs.arg() < rhs.arg();
  return lhs.cross(rhs) > 0;
}
template <typename T>
struct L {
  P<T> a, b;
  explicit L(P<T> a = {}, P<T> b = {}) : a(a), b(b) {}
  P<T> v() { return b - a; }
  bool contains(P<T> p) { return sign((p - a).cross(p - b)) == 0 and sign((p - a).dot(p - b)) <= 0; }
  int left(P<T> p) { return sign(v().cross(p - a)); }
  optional<pair<T, T>> intersection(L l) {
    auto y = v().cross(l.v());
    if (sign(y) == 0) return {};
    auto x = (l.a - a).cross(l.v());
    return y < 0 ? pair(-x, -y) : pair(x, y);
  }
};
template <typename T>
struct G {
  vector<P<T>> g;
  explicit G(int n) : g(n) {}
  explicit G(const vector<P<T>>& g) : g(g) {}
  optional<int> winding(P<T> p) {
    int n = g.size(), res = 0;
    for (int i = 0; i < n; i += 1) {
      auto a = g[i], b = g[(i + 1) % n];
      L l(a, b);
      if (l.contains(p)) return {};
      if (sign(l.v().y) < 0 and l.left(p) >= 0) continue;
      if (sign(l.v().y) == 0) continue;
      if (sign(l.v().y) > 0 and l.left(p) <= 0) continue;
      if (sign(a.y - p.y) < 0 and sign(b.y - p.y) >= 0) res += 1;
      if (sign(a.y - p.y) >= 0 and sign(b.y - p.y) < 0) res -= 1;
    }
    return res;
  }
  G convex() {
    ranges::sort(g, {}, [&](P<T> p) { return pair(p.x, p.y); });
    vector<P<T>> h;
    for (auto p : g) {
      while (ssize(h) >= 2 and sign((h.back() - h.end()[-2]).cross(p - h.back())) <= 0) h.pop_back();
      h.push_back(p);
    }
    int m = h.size();
    for (auto p : g | views::reverse) {
      while (ssize(h) > m and sign((h.back() - h.end()[-2]).cross(p - h.back())) <= 0) h.pop_back();
      h.push_back(p);
    }
    h.pop_back();
    return G(h);
  }
  // Following function are valid only for convex.
  T diameter2() {
    int n = g.size();
    T res = 0;
    for (int i = 0, j = 1; i < n; i += 1) {
      auto a = g[i], b = g[(i + 1) % n];
      while (sign((b - a).cross(g[(j + 1) % n] - g[j])) > 0) j = (j + 1) % n;
      res = max(res, (a - g[j]).len2());
      res = max(res, (a - g[j]).len2());
    }
    return res;
  }
  optional<bool> contains(P<T> p) {
    if (g[0] == p) return {};
    if (g.size() == 1) return false;
    if (L(g[0], g[1]).contains(p)) return {};
    if (L(g[0], g[1]).left(p) <= 0) return false;
    if (L(g[0], g.back()).left(p) > 0) return false;
    int i = *ranges::partition_point(views::iota(2, ssize(g)), [&](int i) { return sign((p - g[0]).cross(g[i] - g[0])) <= 0; });
    int s = L(g[i - 1], g[i]).left(p);
    if (s == 0) return {};
    return s > 0;
  }
  int most(const function<P<T>(P<T>)>& f) {
    int n = g.size();
    auto check = [&](int i) { return sign(f(g[i]).cross(g[(i + 1) % n] - g[i])) >= 0; };
    P<T> f0 = f(g[0]);
    bool check0 = check(0);
    if (not check0 and check(n - 1)) return 0;
    return *ranges::partition_point(views::iota(0, n), [&](int i) -> bool {
      if (i == 0) return true;
      bool checki = check(i);
      int t = sign(f0.cross(g[i] - g[0]));
      if (i == 1 and checki == check0 and t == 0) return true;
      return checki ^ (checki == check0 and t <= 0);
    });
  }
  pair<int, int> tan(P<T> p) {
    return {most([&](P<T> x) { return x - p; }), most([&](P<T> x) { return p - x; })};
  }
  pair<int, int> tan(L<T> l) {
    return {most([&](P<T> _) { return l.v(); }), most([&](P<T> _) { return -l.v(); })};
  }
};

template <typename T>
vector<L<T>> half(vector<L<T>> ls, T bound) {
  // Ranges: bound ^ 6
  auto check = [](L<T> a, L<T> b, L<T> c) {
    auto [x, y] = b.intersection(c).value();
    a = L(a.a * y, a.b * y);
    return a.left(b.a * y + b.v() * x) < 0;
  };
  ls.emplace_back(P(-bound, (T)0), P(-bound, -(T)1));
  ls.emplace_back(P((T)0, -bound), P((T)1, -bound));
  ls.emplace_back(P(bound, (T)0), P(bound, (T)1));
  ls.emplace_back(P((T)0, bound), P(-(T)1, bound));
  ranges::sort(ls, [&](L<T> lhs, L<T> rhs) {
    if (sign(lhs.v().cross(rhs.v())) == 0 and sign(lhs.v().dot(rhs.v())) >= 0) return lhs.left(rhs.a) == -1;
    return argument(lhs.v(), rhs.v());
  });
  deque<L<T>> q;
  for (int i = 0; i < ssize(ls); i += 1) {
    if (i and sign(ls[i - 1].v().cross(ls[i].v())) == 0 and sign(ls[i - 1].v().dot(ls[i].v())) == 1) continue;
    while (q.size() > 1 and check(ls[i], q.back(), q.end()[-2])) q.pop_back();
    while (q.size() > 1 and check(ls[i], q[0], q[1])) q.pop_front();
    if (not q.empty() and sign(q.back().v().cross(ls[i].v())) <= 0) return {};
    q.push_back(ls[i]);
  }
  while (q.size() > 1 and check(q[0], q.back(), q.end()[-2])) q.pop_back();
  while (q.size() > 1 and check(q.back(), q[0], q[1])) q.pop_front();
  return vector<L<T>>(q.begin(), q.end());
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
}