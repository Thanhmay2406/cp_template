#include <bits/stdc++.h>

using namespace std;

struct DSU {
  int n;
  vector <int> par, sz;

  DSU(const int& _n): n(_n) {
    par.assign(n + 5, 0);
    sz.assign(n + 5, 1);
    iota(par.begin(), par.end(), 0);
  }

  int find_set(int u) {
    return par[u] == u ? u : par[u] = find_set(par[u]);
  }

  bool union_sets(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    if (u == v) {
      return false;
    }
    if (sz[u] < sz[v]) {
      swap(u, v);
    }
    par[v] = u;
    sz[v] += sz[u];
    return true;
  }
};
