#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

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
        vector<ll> arr;
        for (ll i = 1; i <= n; i++) {
            ll ai; cin >> ai;
            arr.push_back(ai);
        }

        sort(arr.begin(), arr.end());
        segtree t(arr, n);
        int previ = -1;
        for (int i = 0; i < n-1; i++) {
            if (k < i) break;
            previ = i;
            ll nex = t.query(1, 0, n-1, i+1, i+1);
            ll curCost = t.query(1, 0, n-1, i, i);
            if (k >= (i+1)*(nex-curCost)) {
                t.increment(1, 0, n-1, 0, i, (nex-curCost));
                k -= (i+1)*(nex-curCost);
            } else {
                t.increment(1, 0, n-1, 0, i, k/(i+1));
                k -= (k/(i+1))*(i+1);
            }
        }

        if (k >= n) {
            t.increment(1, 0, n-1, 0, n-1, k/n);
            previ = n-1;
            k -= (k/n)*n;
        }
        cout << "test: " << k << " " << previ << endl;
        ll mn = t.query(1, 0, n-1, previ, previ);
        //cout << previ+1 << " " << mn << " " << (n - previ - 1) << " " << (mn+1) - (1 ? mn == t.query(1, 0, n-1, n-1, n-1) and k > 0 : 0) << endl;
        cout << previ+1 << " " << mn << " " << n - previ - 1 << " " << mn+1 << endl;
        ll length = (previ+1)*mn + (n - previ - 1)*(mn)+(k ? mn != t.query(1, 0, n-1, n-1, n-1) : 0) ;
        cout << length - (n-1) + k << endl;
    }
}