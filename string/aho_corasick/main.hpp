template <int sigma = 26, char first = 'a'>
struct AhoCorasick {
  struct Node : array<int, sigma> {
    int link;
    Node() : link(0) { this->fill(0); }
  };
  vector<Node> nodes;
  AhoCorasick() : nodes(1) {}
  int insert(const string& s) {
    int p = 0;
    for (char c : s) {
      int ci = c - first;
      if (not nodes[p][ci]) {
        nodes[p][ci] = nodes.size();
        nodes.emplace_back();
      }
      p = nodes[p][ci];
    }
    return p;
  }
  void init() {
    queue<int> q;
    q.push(0);
    while (not q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < sigma; i += 1) {
        int &v = nodes[u][i], w = nodes[nodes[u].link][i];
        if (not v) {
          v = w;
          continue;
        }
        nodes[v].link = u ? w : 0;
        q.push(v);
      }
    }
  }
};