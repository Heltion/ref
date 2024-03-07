struct Node {
  static constexpr bool persistent = true;
  static mt19937_64 mt;
  Node *l, *r;
  u64 priority;
  int size, v;
  i64 sum;
  Node(const Node& other) { memcpy(this, &other, sizeof(Node)); }
  Node(int v)
      : v(v), sum(v), priority(mt()), size(1) { l = r = nullptr; }
  Node* update(Node* l, Node* r) {
    Node* p = persistent ? new Node(*this) : this;
    p->l = l;
    p->r = r;
    p->size = (l ? l->size : 0) + 1 + (r ? r->size : 0);
    p->sum = (l ? l->sum : 0) + v + (r ? r->sum : 0);
    return p;
  }
};
mt19937_64 Node::mt;
pair<Node*, Node*> split_by_v(Node* p, int v) {
  if (not p) {
    return {};
  }
  if (p->v < v) {
    auto [l, r] = split_by_v(p->r, v);
    return {p->update(p->l, l), r};
  }
  auto [l, r] = split_by_v(p->l, v);
  return {l, p->update(r, p->r)};
}
pair<Node*, Node*> split_by_size(Node* p, int size) {
  if (not p) {
    return {};
  }
  int l_size = p->l ? p->l->size : 0;
  if (l_size < size) {
    auto [l, r] = split_by_size(p->r, size - l_size - 1);
    return {p->update(p->l, l), r};
  }
  auto [l, r] = split_by_size(p->l, size);
  return {l, p->update(r, p->r)};
}
Node* merge(Node* l, Node* r) {
  if (not l or not r) {
    return l ?: r;
  }
  if (l->priority < r->priority) {
    return r->update(merge(l, r->l), r->r);
  }
  return l->update(l->l, merge(l->r, r));
}