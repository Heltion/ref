minimum_perfect_matching_on_bipartite_graph(const vector<vector<i64>>& w) {
  i64 n = w.size();
  vector<int> rm(n, -1), cm(n, -1);
  vector<i64> pi(n);
  auto resid = [&](int r, int c) { return w[r][c] - pi[c]; };
  for (int c = 0; c < n; c += 1) {
    int r =
        ranges::min(views::iota(0, n), {}, [&](int r) { return w[r][c]; });
    pi[c] = w[r][c];
    if (rm[r] == -1) {
      rm[r] = c;
      cm[c] = r;
    }
  }
  vector<int> cols(n);
  iota(cols.begin(), cols.end(), 0);
  for (int r = 0; r < n; r += 1) {
    if (rm[r] != -1) {
      continue;
    }
    vector<i64> d(n);
    for (int c = 0; c < n; c += 1) {
      d[c] = resid(r, c);
    }
    vector<int> pre(n, r);
    int scan = 0, label = 0, last = 0, col = -1;
    [&]() {
      while (true) {
        if (scan == label) {
          last = scan;
          i64 min = d[cols[scan]];
          for (int j = scan; j < n; j += 1) {
            int c = cols[j];
            if (d[c] <= min) {
              if (d[c] < min) {
                min = d[c];
                label = scan;
              }
              swap(cols[j], cols[label++]);
            }
          }
          for (int j = scan; j < label; j += 1) {
            if (int c = cols[j]; cm[c] == -1) {
              col = c;
              return;
            }
          }
        }
        int c1 = cols[scan++], r1 = cm[c1];
        for (int j = label; j < n; j += 1) {
          int c2 = cols[j];
          i64 len = resid(r1, c2) - resid(r1, c1);
          if (d[c2] > d[c1] + len) {
            d[c2] = d[c1] + len;
            pre[c2] = r1;
            if (len == 0) {
              if (cm[c2] == -1) {
                col = c2;
                return;
              }
              swap(cols[j], cols[label++]);
            }
          }
        }
      }
    }();
    for (int i = 0; i < last; i += 1) {
      int c = cols[i];
      pi[c] += d[c] - d[col];
    }
    for (int t = col; t != -1;) {
      col = t;
      int r = pre[col];
      cm[col] = r;
      swap(rm[r], t);
    }
  }
  i64 res = 0;
  for (int i = 0; i < n; i += 1) {
    res += w[i][rm[i]];
  }
  return {res, rm};
}