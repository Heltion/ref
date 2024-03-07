#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f64 = double_t;
using i128 = __int128_t;
constexpr i64 mod = 998244353;
template <class T, class E, class REV, class OP>
struct Node {
  T t, st;
  bool reversed;
  Node* par;
  array<Node*, 2> ch;
  Node(T t = E()()) : t(t), st(t), reversed(false), par(nullptr) { ch.fill(nullptr); }
  int get_s() {
    if (par == nullptr) {
      return -1;
    }
    if (par->ch[0] == this) {
      return 0;
    }
    if (par->ch[1] == this) {
      return 1;
    }
    return -1;
  }
  void push_up() { st = OP()(ch[0] ? ch[0]->st : E()(), OP()(t, ch[1] ? ch[1]->st : E()())); }
  void reverse() {
    reversed ^= 1;
    st = REV()(st);
  }
  void push_down() {
    if (reversed) {
      swap(ch[0], ch[1]);
      if (ch[0]) {
        ch[0]->reverse();
      }
      if (ch[1]) {
        ch[1]->reverse();
      }
      reversed = false;
    }
  }
  void attach(int s, Node* u) {
    if ((ch[s] = u)) {
      u->par = this;
    }
    push_up();
  }
  void rotate() {
    auto p = par;
    auto pp = p->par;
    int s = get_s();
    int ps = p->get_s();
    p->attach(s, ch[s ^ 1]);
    attach(s ^ 1, p);
    if (~ps) {
      pp->attach(ps, this);
    }
    par = pp;
  }
  void splay() {
    push_down();
    while (~get_s() and ~par->get_s()) {
      par->par->push_down();
      par->push_down();
      push_down();
      (get_s() == par->get_s() ? par : this)->rotate();
      rotate();
    }
    if (~get_s()) {
      par->push_down();
      push_down();
      rotate();
    }
  }
  void access() {
    splay();
    attach(1, nullptr);
    while (par != nullptr) {
      auto p = par;
      p->splay();
      p->attach(1, this);
      rotate();
    }
  }
  void make_root() {
    access();
    reverse();
    push_down();
  }
  void link(Node* u) {
    u->make_root();
    access();
    attach(1, u);
  }
  void cut(Node* u) {
    u->make_root();
    access();
    if (ch[0] == u) {
      ch[0] = u->par = nullptr;
      push_up();
    }
  }
  void set(T t) {
    access();
    this->t = t;
    push_up();
  }
  T query(Node* u) {
    u->make_root();
    access();
    return st;
  }
};
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(20);
  int n, q;
  cin >> n >> q;
  using T = tuple<i64, i64, i64>;
  using E = decltype([]() { return T(1, 0, 0); });
  using REV = decltype([](T t) {
    swap(get<1>(t), get<2>(t));
    return t;
  });
  using OP = decltype([](T t0, T t1) { return T(get<0>(t0) * get<0>(t1) % mod, (get<1>(t0) * get<0>(t1) + get<1>(t1)) % mod, (get<2>(t1) * get<0>(t0) + get<2>(t0)) % mod); });
  vector<Node<T, E, REV, OP>> nodes(n);
  for (int i = 0, a, b; i < n; i += 1) {
    cin >> a >> b;
    nodes[i].set(T(a, b, b));
  }
  for (int i = 1, u, v; i < n; i += 1) {
    cin >> u >> v;
    nodes[u].link(&nodes[v]);
  }
  for (int i = 0, op; i < q; i += 1) {
    cin >> op;
    if (op == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      nodes[u].cut(&nodes[v]);
      nodes[w].link(&nodes[x]);
    }
    if (op == 1) {
      int p, c, d;
      cin >> p >> c >> d;
      nodes[p].set(T(c, d, d));
    }
    if (op == 2) {
      int u, v, x;
      cin >> u >> v >> x;
      auto [c, _, d] = nodes[u].query(&nodes[v]);
      cout << (c * x + d) % mod << "\n";
    }
  }
}