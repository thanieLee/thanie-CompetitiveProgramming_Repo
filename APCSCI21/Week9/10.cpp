#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct segtree {
    vector<ll> t;
    int n;

    segtree(vector<ll> &a, int n) : n(n) {
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }
    void build(vector<ll> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            
            pull(v);
        }
    }
    void pull(int v) {
        t[v] = t[v*2] + t[v*2+1];
    }
    void update(int v, int tl, int tr, int pos, ll val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, val);
            else
                update(v*2+1, tm+1, tr, pos, val);
            
            pull(v);
        }
    }
    ll query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm)) + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};

vector<vector<ll>> dp;
ll solve(ll l, ll r, segtree &t, ll &n) {
    if (l == r) {
        return t.query(1, 0, n-1, l, r);
    } else if (dp[l][r] != -1) {
        return dp[l][r];
    } else {
        ll ans = 1000000000000000000;
        ll range = t.query(1, 0, n-1, l, r);
        for (int i = l; i < r; i++) {
            ans = min(ans, solve(l, i, t, n)+solve(i+1, r, t, n)+range);
        }
        return dp[l][r] = ans;
    }
}

int main(){
    ll n; cin >> n;
    vector<ll> arr;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        arr.push_back(x);
    }
    segtree t(arr, n);
    dp.resize(n+1, vector<ll>(n+1, -1));
    cout << solve(0, n-1, t, n)-t.query(1, 0, n-1, 0, n-1) << endl;
}