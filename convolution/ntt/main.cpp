void fft(vector<i64>& a, bool inverse) {
  int n = a.size();
  vector<int> r(n);
  for (int i = 0; i < n; i += 1) {
    r[i] = r[i / 2] / 2 | (i % 2 ? n / 2 : 0);
  }
  for (int i = 0; i < n; i += 1) {
    if (i < r[i]) {
      swap(a[i], a[r[i]]);
    }
  }
  for (int m = 1; m < n; m *= 2) {
    i64 wn = power(inverse ? power(g, mod - 2) : g, (mod - 1) / m / 2);
    for (int i = 0; i < n; i += m * 2) {
      i64 w = 1;
      for (int j = 0; j < m; j += 1, w = w * wn % mod) {
        auto &x = a[i + j + m], &y = a[i + j], t = w * x % mod;
        tie(x, y) = pair((y + mod - t) % mod, (y + t) % mod);
      }
    }
  }
  if (inverse) {
    i64 inv = power(n, mod - 2);
    for (auto& ai : a) {
      ai = ai * inv % mod;
    }
  }
}