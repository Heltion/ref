vector<int> fborder(const string& s) {
  int n = s.size();
  vector<int> res(n);
  for (int i = 1; i < n; i += 1) {
    int& j = res[i] = res[i - 1];
    while (j and s[i] != s[j]) {
      j = res[j - 1];
    }
    j += s[i] == s[j];
  }
  return res;
}