#include <bits/stdc++.h>

using namespace std;

/*
 * update(pos, x): set a[pos] = x;
 * get(l, r): calculate sum a[l] + a[l + 1] + .... + a[r]
 * */

struct ST {
  int n;
  vector <int> t;

  ST(const vector <int>& a): n(a.size()) {
    t.assign(n * 4, 0);
    build(1, 0, n - 1, a);
  }

  void build(int id, int l, int r, const vector<int>& a) {
    if (l == r) {
      t[id] = a[l];
      return;
    }

    int mid = (l + r) / 2;

    build(id * 2, l, mid, a);
    build(id * 2 + 1, mid + 1, r, a);

    t[id] = t[id * 2] + t[id * 2 + 1];
  }

  void update(int pos, int x, int id, int l, int r) {
    if (pos < l || r < pos) {
      return;
    }

    if (l == r) {
      t[id] = x;
      return;
    }

    int mid = (l + r) / 2;

    update(pos, x, id * 2, l, mid);
    update(pos, x, id * 2 + 1, mid + 1, r);

    t[id] = t[id * 2] + t[id * 2 + 1];
  }

  void update(int pos, int x) { update(pos, x, 1, 0, n - 1); }

  int get_sum(int u, int v, int id, int l, int r) {
    if(v < l || r < u) {
      return 0;
    }

    if (u <= l && r <= v) {
      return t[id];
    }

    int mid = (l + r) / 2;

    int left = get(u, v, id * 2, l, mid);
    int right = get(u, v, id * 2 + 1, mid + 1, r);

    return left + right;
  }

  int get(int l, int r) { return get(l, r, 1, 0, n - 1); }
};
