vector<int> lyndon_factorization(string const &s) {
  int n = s.size();
  vector<int> res = {0};
  for (int i = 0; i < n;) {
    int j = i + 1, k = i;
    for (; j < n and s[k] <= s[j]; j += 1) k = s[k] < s[j] ? i : k + 1;
    while (i <= k) res.push_back(i += j - k);
  }
  return res;
}
