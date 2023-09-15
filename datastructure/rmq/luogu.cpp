// https://www.luogu.com.cn/problem/P3865
#include <bits/stdc++.h>
using namespace std;

struct RangeMinimumQuery {
  vector<vector<int>> table;
  RangeMinimumQuery() {}
  RangeMinimumQuery(const vector<int> &a) {
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

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int &ai : a) {
    cin >> ai;
    ai = -ai;
  }
  RangeMinimumQuery rmq(a);
  for (int qi = 0, l, r; qi < q; qi += 1) {
    cin >> l >> r;
    cout << -rmq.query(l - 1, r) << "\n";
  }
}