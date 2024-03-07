#include <bits/stdc++.h>
using namespace std;
using f64 = double;
constexpr f64 eps = 1e-9;
// Find max cx s.t. ax <= b and x >= 0.
struct Simplex {
  int n, m;
  f64 z;
  vector<vector<f64>> a;
  vector<f64> b, c;
  vector<int> base;
  Simplex(int n, int m) : n(n), m(m), a(m, vector<f64>(n)), b(m), c(n), base(n + m), z(0) { iota(base.begin(), base.end(), 0); }
  void pivot(int out, int in) {
    swap(base[out + n], base[in]);
    f64 f = 1 / a[out][in];
    for (f64& aij : a[out]) {
      aij *= f;
    }
    b[out] *= f;
    a[out][in] = f;
    for (int i = 0; i <= m; i += 1) {
      if (i != out) {
        auto& ai = i == m ? c : a[i];
        f64& bi = i == m ? z : b[i];
        f64 f = -ai[in];
        if (f < -eps or f > eps) {
          for (int j = 0; j < n; j += 1) {
            ai[j] += a[out][j] * f;
          }
          ai[in] = a[out][in] * f;
          bi += b[out] * f;
        }
      }
    }
  }
  bool feasible() {
    while (true) {
      int i = ranges::min_element(b) - b.begin();
      if (b[i] > -eps) {
        break;
      }
      int k = -1;
      for (int j = 0; j < n; j += 1) {
        if (a[i][j] < -eps and (k == -1 or base[j] > base[k])) {
          k = j;
        }
      }
      if (k == -1) {
        return false;
      }
      pivot(i, k);
    }
    return true;
  }
  bool bounded() {
    while (true) {
      int i = ranges::max_element(c) - c.begin();
      if (c[i] < eps) {
        break;
      }
      int k = -1;
      for (int j = 0; j < m; j += 1) {
        if (a[j][i] > eps) {
          if (k == -1) {
            k = j;
          } else {
            f64 d = b[j] * a[k][i] - b[k] * a[j][i];
            if (d < -eps or (d < eps and base[j] > base[k])) {
              k = j;
            }
          }
        }
      }
      if (k == -1) {
        return false;
      }
      pivot(k, i);
    }
    return true;
  }
  vector<f64> x() const {
    vector<f64> res(n);
    for (int i = n; i < n + m; i += 1) {
      if (base[i] < n) {
        res[base[i]] = b[i - n];
      }
    }
    return res;
  }
};

int main() {
  cout << fixed << setprecision(20);
  int n, m, t;
  cin >> n >> m >> t;
  Simplex simplex(n, m);
  for (int i = 0; i < n; i += 1) {
    cin >> simplex.c[i];
  }
  for (int i = 0; i < m; i += 1) {
    for (int j = 0; j < n; j += 1) {
      cin >> simplex.a[i][j];
    }
    cin >> simplex.b[i];
  }
  if (not simplex.feasible()) {
    cout << "Infeasible";
    return 0;
  }
  if (not simplex.bounded()) {
    cout << "Unbounded";
    return 0;
  }
  cout << -simplex.z << "\n";
  if (t) {
    for (f64 xi : simplex.x()) {
      cout << xi << " ";
    }
  }
}