struct Dinic {
  int n;
  vector<tuple<int, int, i64>> e;
  vector<vector<int>> adj;
  vector<int> level;
  Dinic(int n) : n(n), adj(n) {}
  int add(int u, int v, int c) {
    int i = e.size();
    e.emplace_back(u, v, c);
    e.emplace_back(v, u, 0);
    adj[u].push_back(i);
    adj[v].push_back(i ^ 1);
    return i;
  }
  i64 max_flow(int s, int t) {
    i64 flow = 0;
    queue<int> q;
    vector<int> cur;
    auto bfs = [&]() {
      level.assign(n, -1);
      level[s] = 0;
      q.push(s);
      while (not q.empty()) {
        int u = q.front();
        q.pop();
        for (int i : adj[u]) {
          auto [_, v, c] = e[i];
          if (c and level[v] == -1) {
            level[v] = level[u] + 1;
            q.push(v);
          }
        }
      }
      return ~level[t];
    };
    auto dfs = [&](auto &dfs, int u, i64 limit) -> i64 {
      if (u == t) return limit;
      i64 res = 0;
      for (int &i = cur[u]; i < ssize(adj[u]) and limit; i += 1) {
        int j = adj[u][i];
        auto [_, v, c] = e[j];
        if (level[v] == level[u] + 1 and c)
          if (i64 d = dfs(dfs, v, min(c, limit)); d) {
            limit -= d;
            res += d;
            get<2>(e[j]) -= d;
            get<2>(e[j ^ 1]) += d;
          }
      }
      return res;
    };
    while (bfs()) {
      cur.assign(n, 0);
      while (i64 f = dfs(dfs, s, numeric_limits<i64>::max())) flow += f;
    }
    return flow;
  }
};