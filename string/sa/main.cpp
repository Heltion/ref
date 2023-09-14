pair<vector<int>, vector<int>> binary_lifting(const string &s) {
  int n = s.size(), k = 0;
  vector<int> p(n), rank(n), q, count;
  iota(p.begin(), p.end(), 0);
  ranges::sort(p, {}, [&](int i) { return s[i]; });
  for (int i = 0; i < n; i += 1) {
    rank[p[i]] = i and s[p[i]] == s[p[i - 1]] ? rank[p[i - 1]] : k++;
  }
  for (int m = 1; m < n; m *= 2) {
    q.resize(m);
    iota(q.begin(), q.end(), n - m);
    for (int i : p) {
      if (i >= m) { q.push_back(i - m); }
    }
    count.assign(k, 0);
    for (int i : rank) { count[i] += 1; }
    partial_sum(count.begin(), count.end(), count.begin());
    for (int i = n - 1; i >= 0; i -= 1) { p[count[rank[q[i]]] -= 1] = q[i]; }
    auto previous = rank;
    previous.resize(2 * n, -1);
    k = 0;
    for (int i = 0; i < n; i += 1) {
      rank[p[i]] = i and previous[p[i]] == previous[p[i - 1]] and
                           previous[p[i] + m] == previous[p[i - 1] + m]
                       ? rank[p[i - 1]]
                       : k++;
    }
  }
  vector<int> lcp(n);
  k = 0;
  for (int i = 0; i < n; i += 1) {
    if (rank[i]) {
      k = max(k - 1, 0);
      int j = p[rank[i] - 1];
      while (i + k < n and j + k < n and s[i + k] == s[j + k]) { k += 1; }
      lcp[rank[i]] = k;
    }
  }
  return {p, lcp};
}