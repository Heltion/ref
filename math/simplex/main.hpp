template <typename T = long double>
struct Simplex {
  static constexpr T eps = 1e-9;
  int n, m;
  T z;
  vector<vector<T>> a;
  vector<T> b, c;
  vector<int> base;
  Simplex(int n, int m) : n(n), m(m), z(0), a(m, vector<T>(n)), b(m), c(n), base(n + m) {
    for (int i = 0; i < n + m; i += 1) base[i] = i;
  }
  void pivot(int out, int in) {
    swap(base[out + n], base[in]);
    T f = 1 / a[out][in];
    for (T &aij : a[out]) aij *= f;
    b[out] *= f;
    a[out][in] = f;
    for (int i = 0; i <= m; i += 1)
      if (i != out) {
        auto &ai = i == m ? c : a[i];
        T &bi = i == m ? z : b[i];
        T f = -ai[in];
        if (f < -eps or f > eps) {
          for (int j = 0; j < n; j += 1) ai[j] += a[out][j] * f;
          ai[in] = a[out][in] * f;
          bi += b[out] * f;
        }
      }
  }
  bool feasible() {
    while (true) {
      int i = ranges::min_element(b) - b.begin();
      if (b[i] > -eps) break;
      int k = -1;
      for (int j = 0; j < n; j += 1)
        if (a[i][j] < -eps and (k == -1 or base[j] > base[k])) k = j;
      if (k == -1) return false;
      pivot(i, k);
    }
    return true;
  }
  bool bounded() {
    while (true) {
      int i = ranges::max_element(c) - c.begin();
      if (c[i] < eps) break;
      int k = -1;
      for (int j = 0; j < m; j += 1)
        if (a[j][i] > eps) {
          if (k == -1)
            k = j;
          else {
            f64 d = b[j] * a[k][i] - b[k] * a[j][i];
            if (d < -eps or (d < eps and base[j] > base[k])) k = j;
          }
        }
      if (k == -1) return false;
      pivot(k, i);
    }
    return true;
  }
  vector<T> x() const {
    vector<T> res(n);
    for (int i = n; i < n + m; i += 1)
      if (base[i] < n) res[base[i]] = b[i - n];
    return res;
  }
};