#include <bits/stdc++.h>

using namespace std;

#define int long long

/*
 * matrix template using int64 (long long)
 * but i using #define int long long for this :)))
 * */

const int MOD = 1e9 + 7;

struct matrix {
  int n, m;
  vector<vector<int>> arr;
  
  matrix(const int& _n, const int& _m): n(_n), m(_m) {
    arr.assign(n, vector<int>(m, 0));
  }

  matrix operator* (const matrix& other) {
    matrix ans(n, other.m);
    
    for (int i=0 ; i<n ; i++) {
      for (int j=0 ; j<other.m ; j++) {
        for (int k=0 ; k<m ; k++) {
          ans.arr[i][j] = (ans.arr[i][j] + arr[i][k] % MOD * other.arr[k][j] % MOD) % MOD;
        }
      }
    }

    return ans;
  }
};
