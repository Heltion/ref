struct Node {
  int link, len;
  array<int, sigma> next;
  Node() : link(-1), len(0) { next.fill(-1); }
};
struct SuffixAutomaton : vector<Node> {
  SuffixAutomaton() : vector<Node>(1) {}
  int extend(int p, int c) {
    if (~at(p).next[c]) {
      // For online multiple strings.
      int q = at(p).next[c];
      if (at(p).len + 1 == at(q).len) { return q; }
      int clone = size();
      push_back(at(q));
      back().len = at(p).len + 1;
      while (~p and at(p).next[c] == q) {
        at(p).next[c] = clone;
        p = at(p).link;
      }
      at(q).link = clone;
      return clone;
    }
    int cur = size();
    emplace_back();
    back().len = at(p).len + 1;
    while (~p and at(p).next[c] == -1) {
      at(p).next[c] = cur;
      p = at(p).link;
    }
    if (~p) {
      int q = at(p).next[c];
      if (at(p).len + 1 == at(q).len) {
        back().link = q;
      } else {
        int clone = size();
        push_back(at(q));
        back().len = at(p).len + 1;
        while (~p and at(p).next[c] == q) {
          at(p).next[c] = clone;
          p = at(p).link;
        }
        at(q).link = at(cur).link = clone;
      }
    } else {
      back().link = 0;
    }
    return cur;
  }
};