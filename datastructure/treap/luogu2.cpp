// https://www.luogu.com.cn/problem/P5055
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
  Node(int v) : v(v), sum(v), priority(mt()), size(1) { l = r = nullptr; }
  Node *update(Node *l, Node *r) {
    Node *p = persistent ? new Node(*this) : this;
    p->l = l;
    p->r = r;
    p->size = (l ? l->size : 0) + 1 + (r ? r->size : 0);
    p->sum = (l ? l->sum : 0) + v + (r ? r->sum : 0);
    return p;
  }
};
mt19937_64 Node::mt;
pair<Node *, Node *> split_by_v(Node *p, int v) {
  if (not p) { return {}; }
  if (p->v < v) {
    auto [l, r] = split_by_v(p->r, v);
    return {p->update(p->l, l), r};
  }
  auto [l, r] = split_by_v(p->l, v);
  return {l, p->update(r, p->r)};
}
pair<Node *, Node *> split_by_size(Node *p, int size) {
  if (not p) { return {}; }
  int l_size = p->l ? p->l->size : 0;
  if (l_size < size) {
    auto [l, r] = split_by_size(p->r, size - l_size - 1);
    return {p->update(p->l, l), r};
  }
  auto [l, r] = split_by_size(p->l, size);
  return {l, p->update(r, p->r)};
}
Node *merge(Node *l, Node *r) {
  if (not l or not r) { return l ?: r; }
  if (l->priority < r->priority) { return r->update(merge(l, r->l), r->r); }
  return l->update(l->l, merge(l->r, r));
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<Node *> t(n + 1), rt(n + 1);
  i64 last_ans = 0;
  for (int i = 1; i <= n; i += 1) {
    int v, opt;
    i64 a, b;
    cin >> v >> opt >> a;
    if (opt != 2) { cin >> b; }
    a ^= last_ans;
    b ^= last_ans;
    if (opt == 1) {
      int ra = (t[v] ? t[v]->size : 0) - a;
      {
        auto [l, r] = split_by_size(t[v], a);
        t[i] = merge(merge(l, new Node(b)), r);
      }
      {
        auto [l, r] = split_by_size(rt[v], ra);
        rt[i] = merge(merge(l, new Node(b)), r);
      }
    }
    if (opt == 2) {
      int ra = t[v]->size + 1 - a;
      {
        auto [l, r] = split_by_size(t[v], a);
        auto [ll, _] = split_by_size(l, a - 1);
        t[i] = merge(ll, r);
      }
      {
        auto [l, r] = split_by_size(rt[v], ra);
        auto [ll, _] = split_by_size(l, ra - 1);
        rt[i] = merge(ll, r);
      }
    }
    if (opt == 3) {
      int n = t[v]->size;
      auto [l, r] = split_by_size(t[v], b);
      auto [ll, lr] = split_by_size(l, a - 1);
      auto [rl, rr] = split_by_size(rt[v], n + 1 - a);
      auto [rll, rlr] = split_by_size(rl, n - b);
      t[i] = merge(merge(ll, rlr), r);
      rt[i] = merge(merge(rll, lr), rr);
    }
    if (opt == 4) {
      t[i] = t[v];
      rt[i] = rt[v];
      auto [l, r] = split_by_size(t[v], b);
      auto [ll, lr] = split_by_size(l, a - 1);
      last_ans = lr->sum;
      cout << last_ans << "\n";
    }
  }
}