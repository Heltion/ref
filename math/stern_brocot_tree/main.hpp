struct Node {
  int a, b;
  vector<pair<i64, char>> p;
  Node(i64 a, i64 b) : a(a), b(b) {
    assert(gcd(a, b) == 1);
    while (a != 1 or b != 1)
      if (a > b) {
        int k = (a - 1) / b;
        p.emplace_back(k, 'R');
        a -= k * b;
      } else {
        int k = (b - 1) / a;
        p.emplace_back(k, 'L');
        b -= k * a;
      }
  }
  Node(vector<pair<i64, char>> p, i64 _a = 1, i64 _b = 1) : a(_a), b(_b), p(p) {
    for (auto [c, d] : p | views::reverse)
      if (d == 'R')
        a += c * b;
      else
        b += c * a;
  }
};