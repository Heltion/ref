#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
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
  P operator-(P p) { return P(x - p.x, y - p.y); }
  T len2() { return x * x + y * y; }
  T cross(P p) { return x * p.y - y * p.x; }
  T dot(P p) { return x * p.x + y * p.y; }
  bool operator==(P p) { return sign(x - p.x) == 0 and sign(y - p.y) == 0; }
  int arg() { return y < 0 or (y == 0 and x > 0) ? -1 : x or y; }
};
#if __cplusplus <= 202000L
namespace cpp20 {
// For the fucking online judges which do not support cpp20
namespace views {
struct Reverse {
} reverse;
vector<P<i64>> operator|(vector<P<i64>> p, Reverse& r) {
  std::reverse(p.begin(), p.end());
  assert(&r == &reverse);
  return p;
}
pair<int, int> iota(int l, int r) {
  return pair(l, r);
}
}  // namespace views
namespace ranges {
void sort(vector<P<i64>>& p,
          i64 cmp,
          const function<pair<i64, i64>(P<i64>)>& proj) {
  std::sort(p.begin(), p.end(),
            [&](P<i64> a, P<i64> b) { return proj(a) < proj(b); });
  assert(not cmp);
}
int partition_point(pair<int, int> p, const function<bool(int)>& pred) {
  int l = p.first - 1, r = p.second;
  while (l + 1 < r) {
    int m = l + (r - l) / 2;
    if (pred(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  return r;
}
}  // namespace ranges
int ssize(const vector<P<i64>>& p) {
  return p.size();
}
}  // namespace cpp20
using namespace cpp20;
#endif
template <typename T>
bool argument(P<T> lhs, P<T> rhs) {
  if (lhs.arg() != rhs.arg()) { return lhs.arg() < rhs.arg(); }
  return lhs.cross(rhs) > 0;
}
template <typename T>
struct L {
  P<T> a, b;
  L(P<T> a = {}, P<T> b = {}) : a(a), b(b) {}
  P<T> v() { return b - a; }
  bool contains(P<T> p) {
    return sign((p - a).cross(p - b)) == 0 and sign((p - a).dot(p - b)) <= 0;
  }
  int left(P<T> p) { return sign(v().cross(p - a)); }
};
template <typename T>
struct G {
  vector<P<T>> g;
  G(int n) : g(n) {}
  G(const vector<P<T>>& g) : g(g) {}
  optional<int> winding(P<T> p) {
    int n = g.size(), res = 0;
    for (int i = 0; i < n; i += 1) {
      auto a = g[i], b = g[(i + 1) % n];
      L l(a, b);
      if (l.contains(p)) { return {}; }
      if (sign(l.v().y) < 0 and l.left(p) >= 0) { continue; }
      if (sign(l.v().y) == 0) { continue; }
      if (sign(l.v().y) > 0 and l.left(p) <= 0) { continue; }
      if (sign(a.y - p.y) < 0 and sign(b.y - p.y) >= 0) { res += 1; }
      if (sign(a.y - p.y) >= 0 and sign(b.y - p.y) < 0) { res -= 1; }
    }
    return res;
  }
  G convex() {
    ranges::sort(g, {}, [&](P<T> p) { return pair(p.x, p.y); });
    vector<P<T>> h;
    for (auto p : g) {
      while (ssize(h) >= 2 and
             sign((h.back() - h.end()[-2]).cross(p - h.back())) <= 0) {
        h.pop_back();
      }
      h.push_back(p);
    }
    int m = h.size();
    for (auto p : g | views::reverse) {
      while (ssize(h) > m and
             sign((h.back() - h.end()[-2]).cross(p - h.back())) <= 0) {
        h.pop_back();
      }
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
      while (sign((b - a).cross(g[(j + 1) % n] - g[j])) > 0) {
        j = (j + 1) % n;
      }
      res = max(res, (a - g[j]).len2());
      res = max(res, (a - g[j]).len2());
    }
    return res;
  }
  optional<bool> contains(P<T> p) {
    if (g[0] == p) { return {}; }
    if (g.size() == 1) { return false; }
    if (L(g[0], g[1]).contains(p)) { return {}; }
    if (L(g[0], g[1]).left(p) <= 0) { return false; }
    if (L(g[0], g.back()).left(p) > 0) { return false; }
    int i = ranges::partition_point(views::iota(2, ssize(g)), [&](int i) {
      return sign((p - g[0]).cross(g[i] - g[0])) <= 0;
    });
    int s = L(g[i - 1], g[i]).left(p);
    if (s == 0) { return {}; }
    return s > 0;
  }
};

template <typename T>
vector<L<T>> half_plane(vector<L<T>> ls) {
  deque<L<T>> q;
}
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  G<i64> g(n);
  for (auto& [x, y] : g.g) { cin >> x >> y; }
  reverse(g.g.begin(), g.g.end());
  int m;
  cin >> m;
  bool ans = true;
  for (int i = 0; i < m; i += 1) {
    P<i64> q;
    cin >> q.x >> q.y;
    auto c = g.contains(q);
    ans = ans and c and c.value();
  }
  cout << (ans ? "YES" : "NO");
}