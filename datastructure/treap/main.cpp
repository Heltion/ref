mt19937_64 mt;
constexpr bool persistent = true;
struct Node {
  Node *l, *r;
  u64 priority;
  int size, v;
  Node(const Node &other) { memcpy(this, &other, sizeof(Node)); }
  Node(int v) : v(v), priority(mt()), size(1) { l = r = nullptr; }
  Node *update(Node *l, Node *r) {
    Node *p = persistent ? new Node(*this) : this;
    p->l = l;
    p->r = r;
    p->size = (l ? l->size : 0) + 1 + (r ? r->size : 0);
    return p;
  }
};
pair<Node *, Node *> split_by_v(Node *p, int v) {
  if (not p) { return {}; }
  if (p->v < v) {
    auto [l, r] = split_by_v(p->r, v);
    return {p->update(p->l, l), r};
  }
  auto [l, r] = split_by_v(p->l, v);
  return {l, p->update(r, p->r)};
}
Node *merge(Node *l, Node *r) {
  if (not l or not r) { return l ?: r; }
  if (l->priority < r->priority) { return r->update(merge(l, r->l), r->r); }
  return l->update(l->l, merge(l->r, r));
}
Node *find_by_order(Node *p, int order) {
  int size = (p->l ? p->l->size : 0);
  if (order < size) { return find_by_order(p->l, order); }
  if (order == size) { return p; }
  return find_by_order(p->r, order - size - 1);
}
int order_of_key(Node *p, int v) {
  if (not p) { return 0; }
  if (p->v < v) { return (p->l ? p->l->size : 0) + 1 + order_of_key(p->r, v); }
  return order_of_key(p->l, v);
}
Node *prev(Node *p, int v) {
  if (not p) { return nullptr; }
  if (p->v >= v) { return prev(p->l, v); }
  return prev(p->r, v) ?: p;
}
Node *next(Node *p, int v) {
  if (not p) { return nullptr; }
  if (p->v <= v) { return next(p->r, v); }
  return next(p->l, v) ?: p;
}