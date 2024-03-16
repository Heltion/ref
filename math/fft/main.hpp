void fft(vector<complex<f64>>& a, bool inverse = false) {
  int n = a.size();
  vector<int> r(n);
  for (int i = 0; i < n; i += 1) r[i] = r[i / 2] / 2 | (i % 2 ? n / 2 : 0);
  for (int i = 0; i < n; i += 1)
    if (i < r[i]) swap(a[i], a[r[i]]);
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
  if (inverse)
    for (auto& ai : a) ai /= n;
}
string operator*(const string& a, const string& b) {
  vector<complex<f64>> af, bf;
  for (char c : a)
    if (c != '-') af.emplace_back(c - '0', 0);
  for (char c : b)
    if (c != '-') bf.emplace_back(c - '0', 0);
  ranges::reverse(af);
  ranges::reverse(bf);
  int n = bit_ceil(af.size() + bf.size());
  af.resize(n);
  bf.resize(n);
  fft(af);
  fft(bf);
  for (int i = 0; i < n; i += 1) af[i] = af[i] * bf[i];
  fft(af, true);
  vector<int> c;
  for (auto x : af) c.push_back(int(x.real() + .5));
  for (int i = 0; i < ssize(c); i += 1) {
    if (c[i] < 10) continue;
    if (i + 1 == ssize(c)) c.push_back(0);
    c[i + 1] += c[i] / 10;
    c[i] %= 10;
  }
  while (not c.empty() and c.back() == 0) c.pop_back();
  if (c.empty()) return "0";
  string s;
  for (int ci : c) s += '0' + ci;
  if ((a[0] == '-') != (b[0] == '-')) s += '-';
  ranges::reverse(s);
  return s;
}