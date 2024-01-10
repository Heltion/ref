template <class T, class E, class REV, class OP> struct Node {
  T t, st;
  bool reversed;
  Node* par;
  array<Node*, 2> ch;
  Node(T t = E()()) : t(t), st(t), reversed(false), par(nullptr) {
    ch.fill(nullptr);
  }
  int get_s() {
    if (par == nullptr) { return -1; }
    if (par->ch[0] == this) { return 0; }
    if (par->ch[1] == this) { return 1; }
    return -1;
  }
  void push_up() {
    st = OP()(ch[0] ? ch[0]->st : E()(), OP()(t, ch[1] ? ch[1]->st : E()()));
  }
  void reverse() {
    reversed ^= 1;
    st = REV()(st);
  }
  void push_down() {
    if (reversed) {
      swap(ch[0], ch[1]);
      if (ch[0]) { ch[0]->reverse(); }
      if (ch[1]) { ch[1]->reverse(); }
      reversed = false;
    }
  }
  void attach(int s, Node* u) {
    if ((ch[s] = u)) { u->par = this; }
    push_up();
  }
  void rotate() {
    auto p = par;
    auto pp = p->par;
    int s = get_s();
    int ps = p->get_s();
    p->attach(s, ch[s ^ 1]);
    attach(s ^ 1, p);
    if (~ps) { pp->attach(ps, this); }
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