// https://www.luogu.com.cn/problem/P3835
// https://www.luogu.com.cn/problem/P3835
#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using u64 = uint64_t;

struct Node {
  static constexpr bool persistent = true;
  static mt19937_64 mt;
  Node *l, *r;
  u64 priority;
  int size, v;
  i64 sum;
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Node*> tree(n + 1);
  for (int i = 1; i <= n; i += 1) {
    int v, opt, x;
    cin >> v >> opt >> x;
    if (opt == 1) {
      auto [l, r] = split_by_v(tree[v], x);
      tree[i] = merge(merge(l, new Node(x)), r);
    }
    if (opt == 2) {
      auto [l, r] = split_by_v(tree[v], x);
      auto [rl, rr] = split_by_v(r, x + 1);
      if (rl) {
        rl = merge(rl->l, rl->r);
      }
      tree[i] = merge(merge(l, rl), rr);
    }
    if (opt == 3) {
      tree[i] = tree[v];
      auto [l, r] = split_by_v(tree[v], x);
      cout << (l ? l->size : 0) + 1 << "\n";
    }
    if (opt == 4) {
      tree[i] = tree[v];
      auto [l, r] = split_by_size(tree[v], x - 1);
      while (r->l) {
        r = r->l;
      }
      cout << r->v << "\n";
    }
    if (opt == 5) {
      tree[i] = tree[v];
      auto [l, r] = split_by_v(tree[v], x);
      while (l and l->r) {
        l = l->r;
      }
      cout << (l ? l->v : numeric_limits<int>::min() + 1) << "\n";
    }
    if (opt == 6) {
      tree[i] = tree[v];
      auto [l, r] = split_by_v(tree[v], x + 1);
      while (r and r->l) {
        r = r->l;
      }
      cout << (r ? r->v : numeric_limits<int>::max()) << "\n";
    }
  }
}
