vector<int> fp(const string& s) {
  int n = s.size();
  vector<int> p(n * 2 - 1);
  for (int i = 0, j = 0; i < n * 2 - 1; i += 1) {
    if (j + p[j] > i) p[i] = min(j + p[j] - i, p[2 * j - i]);
    while (i >= p[i] and i + p[i] <= 2 * n and ((i - p[i]) % 2 == 0 or s[(i - p[i]) / 2] == s[(i + p[i] + 1) / 2])) p[i] += 1;
    if (i + p[i] > j + p[j]) j = i;
  }
  return p;
}