#include <bits/stdc++.h>

using namespace std;

struct FT {
  int n;
  vector <int> bit;

  FT(const int _n): n(_n) {
    bit.assign(n + 5, 0);
  }
  
  void add(int pos, int val) {
    for (; pos <= n ; pos += pos & -pos) {
      bit[pos] += val;
    }
  }

  int get(int pos) {
    int ans = 0;
    for (; pos > 0 ; pos -= pos & pos) {
      ans += bit[pos];
    }
    return ans;
  }
};
