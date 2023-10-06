void fft(vector<complex<f64>>& a, bool inverse) {
  int n = a.size();
  vector<int> r(n);
  for (int i = 0; i < n; i += 1) {
    r[i] = r[i / 2] / 2 | (i % 2 ? n / 2 : 0);
  }
  for (int i = 0; i < n; i += 1) {
    if (i < r[i]) { swap(a[i], a[r[i]]); }
  }
  for (int m = 1; m < n; m *= 2) {
    complex<f64> wn(exp((inverse ? 1.i : -1.i) * numbers::pi / (f64)m));
    for (int i = 0; i < n; i += m * 2) {
      complex<f64> w = 1;
      for (int j = 0; j < m; j += 1, w = w * wn) {
        auto &x = a[i + j + m], &y = a[i + j], t = w * x;
        tie(x, y) = pair(y - t, y + t);
      }
    }
  }
  if (inverse) {
    for (auto& ai : a) { ai /= n; }
  }
}