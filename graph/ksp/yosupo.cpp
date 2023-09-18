#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

struct Node {
  int v, h;
  i64 w;
  Node *l, *r;
  Node(int v, i64 w) : v(v), w(w), h(1) { l = r = nullptr; }
};
Node *merge(Node *u, Node *v) {
  if (not u or not v) { return u ?: v; }
  if (u->w > v->w) { swap(u, v); }
  Node *p = new Node(*u);
  p->r = merge(u->r, v);
  if (p->r and (not p->l or p->l->h < p->r->h)) { swap(p->l, p->r); }
  p->h = (p->r ? p->r->h : 0) + 1;
  return p;
}
struct Edge {
  int u, v, w;
};
template <typename T>
using minimum_heap = priority_queue<T, vector<T>, greater<T>>;
vector<i64> k_shortest_paths(int n, const vector<Edge> &edges, int s, int t,
                             int k) {
  vector<vector<int>> g(n);
  for (int i = 0; i < ssize(edges); i += 1) { g[edges[i].u].push_back(i); }
  vector<int> par(n, -1), p;
  vector<i64> d(n, -1);
  minimum_heap<pair<i64, int>> pq;
  pq.push({d[s] = 0, s});
  while (not pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();
    if (du > d[u]) { continue; }
    p.push_back(u);
    for (int i : g[u]) {
      auto [_, v, w] = edges[i];
      if (d[v] == -1 or d[v] > d[u] + w) {
        par[v] = i;
        pq.push({d[v] = d[u] + w, v});
      }
    }
  }
  if (d[t] == -1) { return vector<i64>(k, -1); }
  vector<Node *> heap(n);
  for (int i = 0; i < ssize(edges); i += 1) {
    auto [u, v, w] = edges[i];
    if (~d[u] and ~d[v] and par[v] != i) {
      heap[v] = merge(heap[v], new Node(u, d[u] + w - d[v]));
    }
  }
  for (int u : p) {
    if (u != s) { heap[u] = merge(heap[u], heap[edges[par[u]].u]); }
  }
  minimum_heap<pair<i64, Node *>> q;
  if (heap[t]) { q.push({d[t] + heap[t]->w, heap[t]}); }
  vector<i64> res = {d[t]};
  for (int i = 1; i < k and not q.empty(); i += 1) {
    auto [w, p] = q.top();
    q.pop();
    res.push_back(w);
    if (heap[p->v]) { q.push({w + heap[p->v]->w, heap[p->v]}); }
    for (auto c : {p->l, p->r}) {
      if (c) { q.push({w + c->w - p->w, c}); }
    }
  }
  res.resize(k, -1);
  return res;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, s, t, k;
  cin >> n >> m >> s >> t >> k;
  vector<Edge> edges(m);
  for (auto &[u, v, w] : edges) cin >> u >> v >> w;
  auto res = k_shortest_paths(n, edges, s, t, k);
  for (i64 x : res) { cout << x << "\n"; }
  return 0;
}