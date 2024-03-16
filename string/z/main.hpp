vector<int> fz(const string& s) {
  int n = s.size();
  vector<int> z(n);
  for (int i = 1, j = 0; i < n; i += 1) {
    z[i] = max(min(j + z[j] - i, z[i - j]), 0);
    while (s[z[i]] == s[i + z[i]]) z[i] += 1;
    if (i + z[i] > j + z[j]) j = i;
  }
  z[0] = n;
  return z;
}