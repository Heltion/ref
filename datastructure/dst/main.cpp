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