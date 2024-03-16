struct RollbackUnionFind {
  vector<pair<int, int>> stack;
  vector<int> uf;
  RollbackUnionFind(int n) : uf(n, -1) {}
  int find(int u) { return uf[u] < 0 ? u : find(uf[u]); }
  int time() { return ssize(stack); }
  bool merge(int u, int v) {
    if ((u = find(u)) == (v = find(v))) return false;
    if (uf[u] < uf[v]) swap(u, v);
    stack.emplace_back(u, uf[u]);
    uf[v] += uf[u];
    uf[u] = v;
    return true;
  }
  void rollback(int t) {
    while (ssize(stack) > t) {
      auto [u, uf_u] = stack.back();
      stack.pop_back();
      uf[uf[u]] -= uf_u;
      uf[u] = uf_u;
    }
  }
};
struct Skew {
  int u, v;
  i64 w, lazy;
  Skew *chl, *chr;
  static Skew *merge(Skew *x, Skew *y) {
    if (not x) return y;
    if (not y) return x;
    if (x->w > y->w) swap(x, y);
    x->push();
    x->chr = merge(x->chr, y);
    swap(x->chl, x->chr);
    return x;
  }
  Skew(tuple<int, int, i64> e) : lazy(0) {
    tie(u, v, w) = e;
    chl = chr = nullptr;
  }
  void add(i64 x) {
    w += x;
    lazy += x;
  }
  void push() {
    if (chl) chl->add(lazy);
    if (chr) chr->add(lazy);
    lazy = 0;
  }
  Skew *pop() {
    push();
    return merge(chl, chr);
  }
};
pair<i64, vector<int>> directed_minimum_spanning_tree(int n, const vector<tuple<int, int, i64>> &edges, int s) {
  i64 ans = 0;
  vector<Skew *> heap(n), in(n);
  RollbackUnionFind uf(n), rbuf(n);
  vector<pair<Skew *, int>> cycles;
  for (auto [u, v, w] : edges) heap[v] = Skew::merge(heap[v], new Skew({u, v, w}));
  for (int i = 0; i < n; i += 1) {
    if (i == s) continue;
    for (int u = i;;) {
      if (not heap[u]) return {};
      ans += (in[u] = heap[u])->w;
      in[u]->add(-in[u]->w);
      int v = rbuf.find(in[u]->u);
      if (uf.merge(u, v)) break;
      int t = rbuf.time();
      while (rbuf.merge(u, v)) {
        heap[rbuf.find(u)] = Skew::merge(heap[u], heap[v]);
        u = rbuf.find(u);
        v = rbuf.find(in[v]->u);
      }
      cycles.emplace_back(in[u], t);
      while (heap[u] and rbuf.find(heap[u]->u) == rbuf.find(u)) heap[u] = heap[u]->pop();
    }
  }
  for (auto [p, t] : cycles | views::reverse) {
    int u = rbuf.find(p->v);
    rbuf.rollback(t);
    int v = rbuf.find(in[u]->v);
    in[v] = exchange(in[u], p);
  }
  vector<int> res(n, -1);
  for (int i = 0; i < n; i += 1) res[i] = i == s ? i : in[i]->u;
  return {ans, res};
}