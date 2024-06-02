#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll MAX = 1000000000000000000;


struct segtree {
    vector<ll> t, ladd, lset;
    int n;

    segtree(vector<ll> &a, int n) : n(n) {
        t.resize(4*n);
        ladd.resize(4*n, 0);
        lset.resize(4*n, 0);
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
    void push(int v, int tl, int tr) {
            if (lset[v]) {
                if (tl != tr) {
                    lset[v*2] = lset[v*2+1] = lset[v];
                    ladd[v*2] = ladd[v*2+1] = 0;
                }
                t[v] = (tr - tl + 1) * lset[v];
                lset[v] = 0;
            } 
            if (ladd[v]) {
                t[v] += (tr - tl + 1) * ladd[v];

                if (tl != tr) {
                    ladd[v*2] += ladd[v];
                    ladd[v*2+1] += ladd[v];
                }
                
                ladd[v] = 0;
            }
    }
    void increment(int v, int tl, int tr, int l, int r, ll val) {
        push(v, tl, tr);
        if (l > r)
            return;
        if (l == tl and r == tr) {
            ladd[v] += val;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr)/2;
            increment(v*2, tl, tm, l, min(r, tm), val);
            increment(v*2+1, tm+1, tr, max(l, tm+1), r, val);
            pull(v);
        }
    }
    void set(int v, int tl, int tr, int l, int r, ll val) {
        push(v, tl, tr);
        if (l > r)
            return;
        if (l == tl and r == tr) {
            lset[v] = val;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            set(v*2, tl, tm, l, min(r, tm), val);
            set(v*2+1, tm+1, tr, max(l, tm+1), r, val);
            pull(v);
        }
    }


    ll query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r)
            return 0;
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm)) + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};


int main(){
    int t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        vector<ll> arr(n);
        for (int i = 0; i < n; i++) {
            ll ai; cin >> ai;
            arr[i] = ai;
        }
        sort(arr.begin(), arr.end());
        segtree t(arr, n);



        ll cost = 0;
        ll prev = 0;
        for (int i = 1; i < n; i++) {
            cost = arr[i]-arr[i-1];
            prev = i;
            if (k >= cost*i) {
                t.increment(1, 0, n-1, 0, i-1, cost);
                k -= cost*i;
            } else {
                t.increment(1, 0, n-1, 0, i-1, k/i);
                k -= (k/i)*i;
                break;
            }
        }


        if (k > 0){
            t.increment(1, 0, n-1, 0, prev, k/(prev+1));
            k -= (k/(prev+1))*(prev+1);
        }

        if (k%(prev+1) > 0)
                t.increment(1, 0, n-1, 0, k%(prev+1) - 1, 1);

        ll w = MAX;
        for (int i = 0; i < n; i++) {
            w = min(t.query(1, 0, n-1, i, i), w);
        }

        ll ans = n*w + 1;
        for (int i = 0; i < n; i++) {
            if (w == t.query(1, 0, n-1, i, i)) ans--;
        }
        cout << ans << endl;
    }
}
