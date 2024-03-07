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