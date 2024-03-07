#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
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
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int q;
  cin >> q;
  for (int qi = 0; qi < q; qi += 1) {
    string s;
    cin >> s;
    if (s == "DECODE_PATH") {
      int n;
      cin >> n;
      vector<pair<int, char>> p(n);
      for (auto& [c, d] : p) {
        cin >> d >> c;
      }
      Node node(p);
      cout << node.a << " " << node.b << "\n";
    } else if (s == "ENCODE_PATH") {
      int a, b;
      cin >> a >> b;
      Node node(a, b);
      cout << node.p.size() << " ";
      for (auto [c, d] : node.p) {
        cout << d << " " << c << " ";
      }
      cout << "\n";
    } else if (s == "LCA") {
      int a0, b0, a1, b1;
      cin >> a0 >> b0 >> a1 >> b1;
      Node node0(a0, b0), node1(a1, b1);
      vector<pair<int, char>> p;
      for (int i = 0; i < ssize(node0.p) and i < ssize(node1.p); i += 1) {
        if (node0.p[i] == node1.p[i]) {
          p.emplace_back(node0.p[i]);
        } else {
          if (node0.p[i].second == node1.p[i].second) {
            p.emplace_back(min(node0.p[i].first, node1.p[i].first), node0.p[i].second);
          }
          break;
        }
      }
      Node node(p);
      cout << node.a << " " << node.b << "\n";
    } else if (s == "ANCESTOR") {
      int k, a, b;
      cin >> k >> a >> b;
      Node node(a, b);
      int depth = 0;
      for (auto [c, d] : node.p) {
        depth += c;
      }
      if (k > depth) {
        cout << "-1\n";
        continue;
      }
      k = depth - k;
      while (k and not node.p.empty()) {
        int h = node.p.back().first;
        if (k >= h) {
          k -= h;
          node.p.pop_back();
        } else {
          node.p.back().first -= k;
          k = 0;
        }
      }
      if (k) {
        cout << "-1\n";
      } else {
        node = Node(node.p);
        cout << node.a << " " << node.b << "\n";
      }
    } else if (s == "RANGE") {
      int a, b;
      cin >> a >> b;
      Node node(a, b);
      Node node0(node.p, 0, 1), node1(node.p, 1, 0);
      cout << node0.a << " " << node0.b << " " << node1.a << " " << node1.b << "\n";
    }
  }
}
