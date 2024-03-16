template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<>>;
tuple<vector<int>, vector<int>, vector<i64>> shortest_tree(const vector<vector<pair<int, i64>>>& adj, int s) {
  int n = adj.size();
  MinHeap<pair<i64, int>> pq;
  vector<int> p(n, -1), order;
  vector<i64> d(n, -1);
  pq.emplace(d[s] = 0, s);
  while (not pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop();
    if (du != d[u]) continue;
    order.push_back(u);
    for (auto [v, w] : adj[u]) {
      if (d[v] == -1 or d[v] > d[u] + w) {
        p[v] = u;
        pq.emplace(d[v] = d[u] + w, v);
      }
    }
  }
  return {p, order, d};
}
template <class T>
struct Node {
  static int get(Node* x) { return x ? x->d : 0; }
  static Node* merge(Node* x, Node* y) {
    if (not x) return y;
    if (not y) return x;
    if (x->key > y->key) swap(x, y);
    Node* res = new Node(*x);
    res->chr = merge(res->chr, y);
    if (get(res->chr) > get(res->chl)) swap(res->chl, res->chr);
    res->d = get(res->chr) + 1;
    return res;
  }
  int d;
  T key;
  Node *chl, *chr;
  Node(T key) : d(1), key(key) { chl = chr = nullptr; }
};
vector<i64> k_shortest_paths(const vector<vector<pair<int, i64>>>& adj, int s, int t, int k) {
  int n = adj.size();
  auto [p, order, d] = shortest_tree(adj, s);
  vector<i64> res;
  res.push_back(d[t]);
  if (d[t] == -1) return res;
  using Leftist = Node<pair<i64, int>>;
  vector<Leftist*> roots(n);
  vector<int> mul(n);
  for (int u = 0; u < n; u += 1) {
    if (d[u] == -1) continue;
    for (auto [v, w] : adj[u]) {
      if (d[v] == -1) continue;
      w += d[u] - d[v];
      if (p[v] != u or w or exchange(mul[v], 1)) roots[v] = Leftist::merge(roots[v], new Node(pair(w, u)));
    }
  }
  for (int u : order)
    if (u != s) roots[u] = Leftist::merge(roots[u], roots[p[u]]);
  if (not roots[t]) return res;
  MinHeap<pair<i64, Leftist*>> pq;
  pq.emplace(d[t] + roots[t]->key.first, roots[t]);
  while (not pq.empty() and ssize(res) < k) {
    auto [d, p] = pq.top();
    pq.pop();
    res.push_back(d);
    auto [w, v] = p->key;
    for (auto ch : {p->chl, p->chr}) {
      if (ch) pq.emplace(d - w + ch->key.first, ch);
    }
    if (roots[v]) pq.emplace(d + roots[v]->key.first, roots[v]);
  }
  return res;
}