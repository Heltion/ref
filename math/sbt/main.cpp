struct Node {
  int a, b;
  vector<pair<int, char>> p;
  Node(int a, int b) : a(a), b(b) {
    // gcd(a, b) == 1
    while (a != 1 or b != 1) {
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
  }
  Node(vector<pair<int, char>> p, int _a = 1, int _b = 1) : p(p), a(_a), b(_b) {
    for (auto [c, d] : p | views::reverse) {
      if (d == 'R') {
        a += c * b;
      } else {
        b += c * a;
      }
    }
  }
};