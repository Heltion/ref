struct LongestCommonPrefix {
  int n;
  vector<int> p, rank;
  vector<vector<int>> st;
  LongestCommonPrefix(const string &s) : n(s.size()), p(n), rank(n) {
    int k = 0;
    vector<int> q, count;
    for (int i = 0; i < n; i += 1) p[i] = i;
    ranges::sort(p, {}, [&](int i) { return s[i]; });
    for (int i = 0; i < n; i += 1) rank[p[i]] = i and s[p[i]] == s[p[i - 1]] ? rank[p[i - 1]] : k++;
    for (int m = 1; m < n; m *= 2) {
      q.resize(m);
      for (int i = 0; i < m; i += 1) q[i] = n - m + i;
      for (int i : p)
        if (i >= m) q.push_back(i - m);
      count.assign(k, 0);
      for (int i : rank) count[i] += 1;
      for (int i = 1; i < k; i += 1) count[i] += count[i - 1];
      for (int i = n - 1; i >= 0; i -= 1) p[count[rank[q[i]]] -= 1] = q[i];
      auto cur = rank;
      cur.resize(2 * n, -1);
      k = 0;
      for (int i = 0; i < n; i += 1) rank[p[i]] = i and cur[p[i]] == cur[p[i - 1]] and cur[p[i] + m] == cur[p[i - 1] + m] ? rank[p[i - 1]] : k++;
    }
    st.emplace_back(n);
    for (int i = 0, k = 0; i < n; i += 1) {
      if (not rank[i]) continue;
      k = max(k - 1, 0);
      int j = p[rank[i] - 1];
      while (i + k < n and j + k < n and s[i + k] == s[j + k]) k += 1;
      st[0][rank[i]] = k;
    }
    for (int i = 1; (1 << i) < n; i += 1) {
      st.emplace_back(n - (1 << i) + 1);
      for (int j = 0; j <= n - (1 << i); j += 1) st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
  int get(int i, int j) {
    if (i == j) return n - i;
    if (i == n or j == n) return 0;
    i = rank[i];
    j = rank[j];
    if (i > j) swap(i, j);
    int k = bit_width(u64(j - i)) - 1;
    return min(st[k][i + 1], st[k][j - (1 << k) + 1]);
  }
};
vector<tuple<int, int, int>> run(const string &s) {
  int n = s.size();
  auto r = s;
  ranges::reverse(r);
  LongestCommonPrefix lcp(s), lcs(r);
  vector<tuple<int, int, int>> runs;
  for (bool inv : {false, true}) {
    vector<int> lyn(n, n), stack;
    for (int i = 0; i < n; i += 1) {
      while (not stack.empty()) {
        int j = stack.back(), k = lcp.get(i, j);
        if (i + k < n and ((s[i + k] > s[j + k]) ^ inv)) break;
        lyn[j] = i;
        stack.pop_back();
      }
      stack.push_back(i);
    }
    for (int i = 0; i < n; i += 1) {
      int j = lyn[i], t = j - i, l = i - lcs.get(n - i, n - j), r = j + lcp.get(i, j);
      if (r - l >= 2 * t) runs.emplace_back(t, l, r);
    }
  }
  ranges::sort(runs);
  runs.erase(ranges::unique(runs).begin(), runs.end());
  return runs;
}