// https://judge.yosupo.jp/problem/directedmst

#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Edge {
  int u, v, w;
};
struct RollbackDisjointSetUnion {
  vector<pair<int, int>> stack;
  vector<int> dsu;
  RollbackDisjointSetUnion(int n)
      : dsu(n, -1) {}
  int find(int u) { return dsu[u] < 0 ? u : find(dsu[u]); }
  int time() { return ssize(stack); }
  bool merge(int u, int v) {
    if ((u = find(u)) == (v = find(v))) {
      return false;
    }
    if (dsu[u] < dsu[v]) {
      swap(u, v);
    }
    stack.emplace_back(u, dsu[u]);
    dsu[v] += dsu[u];
    dsu[u] = v;
    return true;
  }
  void rollback(int t) {
    while (ssize(stack) > t) {
      auto [u, dsu_u] = stack.back();
      stack.pop_back();
      dsu[dsu[u]] -= dsu_u;
      dsu[u] = dsu_u;
    }
  }
};
struct Node {
  Edge e;
  int d;
  Node *l, *r;
  Node(Edge e)
      : e(e), d(0) { l = r = nullptr; }
  void add(int v) {
    e.w += v;
    d += v;
  }
  void push() {
    if (l) {
      l->add(d);
    }
    if (r) {
      r->add(d);
    }
    d = 0;
  }
};
Node* merge(Node* u, Node* v) {
  if (not u or not v) {
    return u ?: v;
  }
  if (u->e.w > v->e.w) {
    swap(u, v);
  }
  u->push();
  u->r = merge(u->r, v);
  swap(u->l, u->r);
  return u;
}
void pop(Node*& u) {
  u->push();
  u = merge(u->l, u->r);
}
pair<i64, vector<int>>
directed_minimum_spanning_tree(int n, const vector<Edge>& edges, int s) {
  i64 ans = 0;
  vector<Node*> heap(n), edge(n);
  RollbackDisjointSetUnion dsu(n), rbdsu(n);
  vector<pair<Node*, int>> cycles;
  for (auto e : edges) {
    heap[e.v] = merge(heap[e.v], new Node(e));
  }
  for (int i = 0; i < n; i += 1) {
    if (i == s) {
      continue;
    }
    for (int u = i;;) {
      if (not heap[u]) {
        return {};
      }
      ans += (edge[u] = heap[u])->e.w;
      edge[u]->add(-edge[u]->e.w);
      int v = rbdsu.find(edge[u]->e.u);
      if (dsu.merge(u, v)) {
        break;
      }
      int t = rbdsu.time();
      while (rbdsu.merge(u, v)) {
        heap[rbdsu.find(u)] = merge(heap[u], heap[v]);
        u = rbdsu.find(u);
        v = rbdsu.find(edge[v]->e.u);
      }
      cycles.emplace_back(edge[u], t);
      while (heap[u] and rbdsu.find(heap[u]->e.u) == rbdsu.find(u)) {
        pop(heap[u]);
      }
    }
  }
  for (auto [p, t] : cycles | views::reverse) {
    int u = rbdsu.find(p->e.v);
    rbdsu.rollback(t);
    int v = rbdsu.find(edge[u]->e.v);
    edge[v] = exchange(edge[u], p);
  }
  vector<int> res(n, -1);
  for (int i = 0; i < n; i += 1) {
    res[i] = i == s ? i : edge[i]->e.u;
  }
  return {ans, res};
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, s;
  cin >> n >> m >> s;
  vector<Edge> edges(m);
  for (auto& [u, v, w] : edges) {
    cin >> u >> v >> w;
  }
  auto p = directed_minimum_spanning_tree(n, edges, s);
  cout << p.first << "\n";
  for (int x : p.second) {
    cout << x << " ";
  }
  return 0;
}