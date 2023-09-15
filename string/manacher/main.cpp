vector<int> manacher(const string &s) {
  int n = s.size();
  vector<int> p(n);
  for (int i = 0, j = 0; i < n; i += 1) {
    if (j + p[j] > i) { p[i] = min(p[j * 2 - i], j + p[j] - i); }
    while (i >= p[i] and i + p[i] < n and s[i - p[i]] == s[i + p[i]]) {
      p[i] += 1;
    }
    if (i + p[i] > j + p[j]) { j = i; }
  }
  return p;
}
