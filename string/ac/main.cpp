constexpr int sigma = 26;
struct Node {
  int link;
  array<int, sigma> next;
  Node() : link(0) { next.fill(0); }
};
struct AhoCorasick : vector<Node> {
  AhoCorasick() : vector<Node>(1) {}
  int add(const string &s, char first = 'a') {
    int p = 0;
    for (char si : s) {
      int c = si - first;
      if (not at(p).next[c]) {
        at(p).next[c] = size();
        emplace_back();
      }
      p = at(p).next[c];
    }
    return p;
  }
  void init() {
    queue<int> q;
    for (int i = 0; i < sigma; i += 1) {
      if (at(0).next[i]) { q.push(at(0).next[i]); }
    }
    while (not q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < sigma; i += 1) {
        if (at(u).next[i]) {
          at(at(u).next[i]).link = at(at(u).link).next[i];
          q.push(at(u).next[i]);
        } else {
          at(u).next[i] = at(at(u).link).next[i];
        }
      }
    }
  }
};