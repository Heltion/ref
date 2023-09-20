struct SparseTable {
  vector<vector<int>> table;
  SparseTable() {}
  SparseTable(const vector<int> &a) {
    int n = a.size(), h = bit_width(a.size());
    table.resize(h);
    table[0] = a;
    for (int i = 1; i < h; i += 1) {
      table[i].resize(n - (1 << i) + 1);
      for (int j = 0; j + (1 << i) <= n; j += 1) {
        table[i][j] = min(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int query(int l, int r) {
    int h = bit_width(unsigned(r - l)) - 1;
    return min(table[h][l], table[h][r - (1 << h)]);
  }
};
struct DisjointSparseTable {
  vector<vector<int>> table;
  DisjointSparseTable(const vector<int> &a) {
    int h = bit_width(a.size() - 1), n = a.size();
    table.resize(h, a);
    for (int i = 0; i < h; i += 1) {
      for (int j = 0; j + (1 << i) < n; j += (2 << i)) {
        for (int k = j + (1 << i) - 2; k >= j; k -= 1) {
          table[i][k] = min(table[i][k], table[i][k + 1]);
        }
        for (int k = j + (1 << i) + 1; k < j + (2 << i) and k < n; k += 1) {
          table[i][k] = min(table[i][k], table[i][k - 1]);
        }
      }
    }
  }
  int query(int l, int r) {
    if (l + 1 == r) { return table[0][l]; }
    int i = bit_width(unsigned(l ^ (r - 1))) - 1;
    return min(table[i][l], table[i][r - 1]);
  }
};