#include <bits/stdc++.h>

using namespace std;

struct LCA {
  int n, LOG;
  vector<vector<int>> up;
  vector<int> dep;
  vector<vector<int>> adj;

  LCA(int _n) : n(_n) {
    LOG = __lg(n) + 1;
    up.assign(LOG, vector<int>(n + 1, 0));
    dep.assign(n + 1, 0);
    adj.assign(n + 1, {});
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs(int u, int p) {
    up[u][0] = p;
    for (int v : adj[u]) {
      if (v == p)
        continue;
      dep[v] = dep[u] + 1;
      dfs(v, u);
    }
  }

  void build(int root = 1) { dfs(root, root); }

  int get_lca(int u, int v) {
    if (dep[u] < dep[v])
      swap(u, v);

    int k = dep[u] - dep[v];

    for (int i = LOG - 1; i >= 0; i--) {
      if ((k >> i) & 1)
        u = up[u][i];
    }

    if (u == v)
      return u;

    for (int i = LOG - 1; i >= 0; i--) {
      if (up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];
      }
    }

    return up[u][0];
  }

  int distance(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[get_lca(u, v)];
  }
};
