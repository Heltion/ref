struct HighestLabelPreflowPush {
  int n;
  vector<vector<int>> g;
  vector<Edge> edges;
  HighestLabelPreflowPush(int n)
      : n(n), g(n) {}
  int add(int u, int v, i64 f) {
    if (u == v) {
      return -1;
    }
    int i = ssize(edges);
    edges.push_back({u, v, f});
    g[u].push_back(i);
    edges.push_back({v, u, 0});
    g[v].push_back(i + 1);
    return i;
  }
  i64 max_flow(int s, int t) {
    vector<i64> p(n);
    vector<int> h(n), cur(n), count(n * 2);
    vector<vector<int>> pq(n * 2);
    auto push = [&](int i, i64 f) {
      auto [u, v, _] = edges[i];
      if (not p[v] and f) {
        pq[h[v]].push_back(v);
      }
      edges[i].f -= f;
      edges[i ^ 1].f += f;
      p[u] -= f;
      p[v] += f;
    };
    h[s] = n;
    count[0] = n - 1;
    p[t] = 1;
    for (int i : g[s]) {
      push(i, edges[i].f);
    }
    for (int hi = 0;;) {
      while (pq[hi].empty()) {
        if (not hi--) {
          return -p[s];
        }
      }
      int u = pq[hi].back();
      pq[hi].pop_back();
      while (p[u] > 0) {
        if (cur[u] == ssize(g[u])) {
          h[u] = n * 2 + 1;
          for (int i = 0; i < ssize(g[u]); i += 1) {
            auto [_, v, f] = edges[g[u][i]];
            if (f and h[u] > h[v] + 1) {
              h[u] = h[v] + 1;
              cur[u] = i;
            }
          }
          count[h[u]] += 1;
          if (not(count[hi] -= 1) and hi < n) {
            for (int i = 0; i < n; i += 1) {
              if (h[i] > hi and h[i] < n) {
                count[h[i]] -= 1;
                h[i] = n + 1;
              }
            }
          }
          hi = h[u];
        } else {
          int i = g[u][cur[u]];
          auto [_, v, f] = edges[i];
          if (f and h[u] == h[v] + 1) {
            push(i, min(p[u], f));
          } else {
            cur[u] += 1;
          }
        }
      }
    }
    return i64(0);
  }
};

struct Dinic {
  int n;
  vector<vector<int>> g;
  vector<Edge> edges;
  vector<int> level;
  Dinic(int n)
      : n(n), g(n) {}
  int add(int u, int v, i64 f) {
    if (u == v) {
      return -1;
    }
    int i = ssize(edges);
    edges.push_back({u, v, f});
    g[u].push_back(i);
    edges.push_back({v, u, 0});
    g[v].push_back(i + 1);
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
        for (int i : g[u]) {
          auto [_, v, c] = edges[i];
          if (c and level[v] == -1) {
            level[v] = level[u] + 1;
            q.push(v);
          }
        }
      }
      return ~level[t];
    };
    auto dfs = [&](auto& dfs, int u, i64 limit) -> i64 {
      if (u == t) {
        return limit;
      }
      i64 res = 0;
      for (int& i = cur[u]; i < ssize(g[u]) and limit; i += 1) {
        int j = g[u][i];
        auto [_, v, f] = edges[j];
        if (level[v] == level[u] + 1 and f) {
          if (i64 d = dfs(dfs, v, min(f, limit)); d) {
            limit -= d;
            res += d;
            edges[j].f -= d;
            edges[j ^ 1].f += d;
          }
        }
      }
      return res;
    };
    while (bfs()) {
      cur.assign(n, 0);
      while (i64 f = dfs(dfs, s, numeric_limits<i64>::max())) {
        flow += f;
      }
    }
    return flow;
  }
};