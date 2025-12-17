#include <bits/stdc++.h>
using namespace std;

template <class S, class F> struct LazySegmentTree {
  int n;
  vector<S> tree;
  vector<F> lazy;

  S e;
  F id;
  function<S(S, S)> op;
  function<S(F, S)> mapping;
  function<F(F, F)> composition;

  LazySegmentTree(int _n, S _e, F _id, function<S(S, S)> _op,
                  function<S(F, S)> _mapping, function<F(F, F)> _composition)
      : n(_n), e(_e), id(_id), op(_op), mapping(_mapping),
        composition(_composition) {
    tree.assign(4 * n, e);
    lazy.assign(4 * n, id);
  }

  void push(int node) {
    if (lazy[node] == id)
      return;

    tree[2 * node] = mapping(lazy[node], tree[2 * node]);
    lazy[2 * node] = composition(lazy[node], lazy[2 * node]);

    tree[2 * node + 1] = mapping(lazy[node], tree[2 * node + 1]);
    lazy[2 * node + 1] = composition(lazy[node], lazy[2 * node + 1]);

    lazy[node] = id;
  }

  void build(const vector<S> &a, int node, int start, int end) {
    if (start == end) {
      if (start < a.size())
        tree[node] = a[start];
      else
        tree[node] = e;
    } else {
      int mid = (start + end) / 2;
      build(a, 2 * node, start, mid);
      build(a, 2 * node + 1, mid + 1, end);
      tree[node] = op(tree[2 * node], tree[2 * node + 1]);
    }
  }

  void build(const vector<S> &a) { build(a, 1, 0, n - 1); }

  void update(int node, int start, int end, int l, int r, F val) {
    if (r < start || end < l)
      return;

    if (l <= start && end <= r) {
      tree[node] = mapping(val, tree[node]);
      lazy[node] = composition(val, lazy[node]);
      return;
    }

    push(node);
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, val);
    update(2 * node + 1, mid + 1, end, l, r, val);
    tree[node] = op(tree[2 * node], tree[2 * node + 1]);
  }

  void update(int l, int r, F val) { update(1, 0, n - 1, l, r, val); }

  S query(int node, int start, int end, int l, int r) {
    if (r < start || end < l)
      return e;
    if (l <= start && end <= r)
      return tree[node];

    push(node);
    int mid = (start + end) / 2;
    return op(query(2 * node, start, mid, l, r),
              query(2 * node + 1, mid + 1, end, l, r));
  }

  S query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
