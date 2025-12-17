#include <bits/stdc++.h>

using namespace std;

template <class T> struct SegmentTree {
  int n;
  vector<T> tree;
  T identity;
  function<T(T, T)> op;

  SegmentTree(int _n, T _identity, function<T(T, T)> _op)
      : n(_n), identity(_identity), op(_op) {
    tree.assign(4 * n, identity);
  }

  void build(const vector<T> &a, int node, int start, int end) {
    if (start == end) {
      if (start < a.size())
        tree[node] = a[start];
      else
        tree[node] = identity;
    } else {
      int mid = (start + end) / 2;
      build(a, 2 * node, start, mid);
      build(a, 2 * node + 1, mid + 1, end);
      tree[node] = op(tree[2 * node], tree[2 * node + 1]);
    }
  }

  void build(const vector<T> &a) { build(a, 1, 0, n - 1); }

  void update(int node, int start, int end, int pos, T val) {
    if (start == end) {
      tree[node] = val;
    } else {
      int mid = (start + end) / 2;
      if (start <= pos && pos <= mid) {
        update(2 * node, start, mid, pos, val);
      } else {
        update(2 * node + 1, mid + 1, end, pos, val);
      }
      tree[node] = op(tree[2 * node], tree[2 * node + 1]);
    }
  }

  void update(int pos, T val) { update(1, 0, n - 1, pos, val); }

  T query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
      return identity;
    }
    if (l <= start && end <= r) {
      return tree[node];
    }
    int mid = (start + end) / 2;
    T p1 = query(2 * node, start, mid, l, r);
    T p2 = query(2 * node + 1, mid + 1, end, l, r);
    return op(p1, p2);
  }

  T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
