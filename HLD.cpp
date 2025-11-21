#include <bits/stdc++.h>

using namespace std;

/*
 * this is submition for problem "Path Queries - CSES"
 *
 * */

#define int long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define el '\n'
#define FOR(i, a, b) for (int i=(a), _b = (b) ; i<=_b ; i++)
#define FORD(i, b, a) for (int i=(b), _a = (a) ; i>=_a ; i--)
#define REP(i, n) for (int i=0, _n=(n) ; i<_n ; i++)
#define fi first
#define se second
 
const int N = 2e5 + 5;
int n, q, a[N];
vector <int> adj[N];
int sz[N], par[N], depth[N], heavy[N];
int head[N], Time, pos[N];
int t[N << 2];
 
void dfs(int u = 1, int p = 1) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        par[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
        if (!heavy[u] || sz[ heavy[u] ] < sz[v]) {
            heavy[u] = v;
        }
    }
}
 
void HLD(int u = 1, int h = 1) {
    head[u] = h;
    pos[u] = ++Time;
    if (heavy[u]) HLD(heavy[u], h);
    for (int v : adj[u]) {
        if (v == heavy[u] || v == par[u]) continue;
        HLD(v, v);
    }
}
 
void update(int pos, int x, int id=1, int l=1, int r=n) {
    if (pos < l || pos > r) return;
    if (l == r) return t[id] = x, void();
    int mid = l + r >> 1;
    update(pos, x, id << 1, l, mid);
    update(pos, x, id << 1 | 1, mid + 1, r);
    t[id] = t[id << 1] + t[id << 1 | 1];
}
 
int get(int u, int v, int id=1, int l=1, int r=n) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return t[id];
    int mid = l + r >> 1;
    return get(u, v, id << 1, l, mid) + get(u, v, id << 1 | 1, mid + 1, r);
}
 
int sum_path(int u, int v) {
    int ans = 0;
    while(head[u] != head[v]) {
        if (depth[u] < depth[v]) swap(u, v);
        ans += get(pos[ head[u] ], pos[u]);
        u = par[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    ans += get(pos[u], pos[v]);
    return ans;
}
 
void solve() {
    cin >> n >> q;
    FOR(i, 1, n) cin >> a[i];
    REP(_, n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs();
    HLD();
    FOR(i, 1, n) update(pos[i], a[i]);
    while(q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, x;
            cin >> u >> x;
            update(pos[u], x);
        }
        else {
            int u;
            cin >> u;
            cout << sum_path(1, u) << el;
        }
    }
}
 
int32_t main() {
    cin.tie(0) -> sync_with_stdio(false);
    
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("err.txt", "w", stderr);
#endif
 
    int T = 1;
 
    //cin >> T;
 
    FOR(i, 1, T) solve();
 
    return 0;
}
