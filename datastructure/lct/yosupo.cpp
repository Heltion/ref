// https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Node {
  i64 v, sum;
  array<Node *, 2> c;
  Node *p;
  bool flip;
  Node(i64 v) : v(v), sum(v), p(nullptr) { c.fill(nullptr); }
  int side() {
    if (not p) { return -1; }
    if (p->c[0] == this) { return 0; }
    if (p->c[1] == this) { return 1; }
    return -1;
  }
  void up() { sum = (c[0] ? c[0]->sum : 0) + v + (c[1] ? c[1]->sum : 0); }
  void down() {
    if (flip) {
      swap(c[0], c[1]);
      if (c[0]) { c[0]->flip ^= 1; }
      if (c[1]) { c[1]->flip ^= 1; }
      flip ^= 1;
    }
  }
  void attach(int s, Node *u) {
    c[s] = u;
    if (u) { u->p = this; }
    up();
  }
  void rotate() {
    auto p = this->p;
    auto pp = p->p;
    int s = side();
    int ps = p->side();
    auto b = c[s ^ 1];
    p->attach(s, b);
    attach(s ^ 1, p);
    if (~ps) { pp->attach(ps, this); }
    this->p = pp;
  }
  void splay() {
    down();
    while (side() >= 0 and p->side() >= 0) {
      p->p->down();
      p->down();
      down();
      (side() == p->side() ? p : this)->rotate();
      rotate();
    }
    if (side() >= 0) {
      p->down();
      down();
      rotate();
    }
  }
  void access() {
    splay();
    attach(1, nullptr);
    while (p != nullptr) {
      auto w = p;
      w->splay();
      w->attach(1, this);
      rotate();
    }
  }
  void reroot() {
    access();
    flip ^= 1;
    down();
  }
  void link(Node *u) {
    u->reroot();
    access();
    attach(1, u);
  }
  void cut(Node *u) {
    u->reroot();
    access();
    if (c[0] == u) {
      c[0] = nullptr;
      u->p = nullptr;
      up();
    }
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  vector<Node *> t(n);
  for (int i = 0; i < n; i += 1) {
    i64 v;
    cin >> v;
    t[i] = new Node(v);
  }
  for (int i = 1, u, v; i < n; i += 1) {
    cin >> u >> v;
    t[u]->link(t[v]);
  }
  for (int qi = 0; qi < q; qi += 1) {
    int op;
    cin >> op;
    if (op == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      t[u]->cut(t[v]);
      t[w]->link(t[x]);
    } else if (op == 1) {
      int p, x;
      cin >> p >> x;
      t[p]->access();
      t[p]->v += x;
      t[p]->sum += x;
    } else {
      int u, v;
      cin >> u >> v;
      t[u]->reroot();
      t[v]->access();
      cout << t[v]->sum << "\n";
    }
  }
}
