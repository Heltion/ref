void fft(vector<complex<f64>> &a, bool inverse) {
  int n = a.size();
  vector<int> r(n);
  for (int i = 0; i < n; i += 1) { r[i] = r[i / 2] / 2 | (i % 2 ? n / 2 : 0); }
  for (int i = 0; i < n; i += 1) {
    if (i < r[i]) { swap(a[i], a[r[i]]); }
  }
  for (int m = 1; m < n; m *= 2) {
    complex<f64> wn(cos(numbers::pi / m),
                    sin((inverse ? -1 : 1) * numbers::pi / m));
    for (int i = 0; i < n; i += m * 2) {
      complex<f64> w = 1;
      for (int j = 0; j < m; j += 1, w = w * wn) {
        auto &x = a[i + j + m], &y = a[i + j], t = w * x;
        tie(x, y) = pair(y - t, y + t);
      }
    }
  }
  if (inverse) {
    for (auto &ai : a) { ai /= n; }
  }
}
vector<int> covolution(const vector<int> &a, const vector<int> &b) {
  auto m = a.size() + b.size() - 1;
  auto n = bit_ceil(m);
  vector<complex<f64>> f(n);
  for (int i = 0; i < (int)n; i += 1) {
    f[i] = {i < ssize(a) ? (f64)a[i] : 0., i < ssize(b) ? (f64)b[i] : 0.};
  }
  fft(f, false);
  for (auto &fi : f) { fi *= fi; }
  fft(f, true);
  vector<int> c(m);
  for (int i = 0; i < (int)m; i += 1) { c[i] = round(f[i].imag() / 2); }
  return c;
}