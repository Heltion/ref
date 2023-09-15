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