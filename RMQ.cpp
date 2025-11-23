#include <bits/stdc++.h>

using namespace std;

struct RMQ {
  int n, K;
  vector<vector<int>> st;
  vector<int> lg;

  RMQ(const vector<int> &a) {
    n = a.size();
    K = __lg(n) + 1;

    st.assign(K, vector<int>(n));
    lg.assign(n + 1, 0);

    // build log table
    for (int i = 2; i <= n; i++) {
      lg[i] = lg[i / 2] + 1;
    }

    // base layer
    for (int i = 0; i < n; i++) {
      st[i][0] = a[i];
    }

    // build
    for (int k = 1; k < K; k++) {
      for (int i = 0; i + (1 << k) <= n; i++) {
        st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
      }
    }
  }

  int query(int l, int r) {
    int k = lg[r - l + 1];
    return min(st[k][l], st[k][r - (1 << k) + 1]);
  }
};
