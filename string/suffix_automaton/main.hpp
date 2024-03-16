template <int sigma = 26, char first = 'a'>
struct SuffixAutomaton {
  struct Node : array<int, sigma> {
    int link, len;
    Node() : link(-1), len(0) { this->fill(-1); }
  };
  vector<Node> nodes;
  SuffixAutomaton() : nodes(1) {}
  int extend(int p, char c) {
    int ci = c - first;
    if (~nodes[p][ci]) {
      int q = nodes[p][ci];
      if (nodes[p].len + 1 == nodes[q].len) return q;
      int clone = nodes.size();
      nodes.push_back(nodes[q]);
      nodes.back().len = nodes[p].len + 1;
      while (~p and nodes[p][ci] == q) {
        nodes[p][ci] = clone;
        p = nodes[p].link;
      }
      nodes[q].link = clone;
      return clone;
    }
    int cur = nodes.size();
    nodes.emplace_back();
    nodes.back().len = nodes[p].len + 1;
    while (~p and nodes[p][ci] == -1) {
      nodes[p][ci] = cur;
      p = nodes[p].link;
    }
    if (~p) {
      int q = nodes[p][ci];
      if (nodes[p].len + 1 == nodes[q].len)
        nodes.back().link = q;
      else {
        int clone = nodes.size();
        nodes.push_back(nodes[q]);
        nodes.back().len = nodes[p].len + 1;
        while (~p and nodes[p][ci] == q) {
          nodes[p][ci] = clone;
          p = nodes[p].link;
        }
        nodes[q].link = nodes[cur].link = clone;
      }
    } else
      nodes.back().link = 0;
    return cur;
  }
};