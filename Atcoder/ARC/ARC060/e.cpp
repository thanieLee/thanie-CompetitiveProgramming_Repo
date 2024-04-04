#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

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
        t[v] = min(t[v*2], t[v*2+1]);
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
            return 10000000000;
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};

int main(){
    int n; cin >> n;
    vector<ll> x, y;
    for (int i = 0; i < n; i++){
        int xi, yi; cin >> xi >> yi;
        if (yi > xi) swap(xi, yi);
        x.push_back(xi);
        y.push_back(yi);
    }

    ll mx = -1, mn = 2000000000, mxi = -1, mni = -1;
    for (int i = 0; i < n; i++){
        int xi = x[i], yi = y[i];
        if (xi > mx) {
            mx = xi;
            mxi = i;
        } else if (xi == mx) {
            if (y[i] > y[mxi] ) {
                mxi = i;
            }
        }

        if (mn > yi) {
            mn = yi;
            mni = i;
        } else if (yi == mn) {
            if (x[mni] > x[i] or (mxi == mni)) {
                mni = i;
            }
        }
    }

    ll rMax = mx, rMin = min(mx, x[mni]), bMax = max(mn, y[mxi]), bMin = mn;


    for (int i = 0; i < n; i++){
        if (i == mni or i == mxi) continue;
        rMin = min(x[i], rMin);
        bMax = max(y[i], bMax);
    }

    ll ans = (rMax-rMin)*(bMax-bMin);
    if (mni != mxi and n > 2) {
        if ((rMax-bMin)*(bMax-rMin) > 0)
            ans = min(ans, (rMax-bMin)*(bMax-rMin));
        vector<pll> test;
        for (int i = 0; i < n; i++) {
            if (i == mni or i == mxi) continue;
            test.push_back({y[i], x[i]});
        }

        sort(test.begin(), test.end());

        vector<ll> small, big;
        for (int i = 0; i < test.size(); i++){
            small.push_back(test[i].first);
            big.push_back(test[i].second);
        }

        segtree smalltree(small, small.size()), bigtree(big, big.size());

        ll newSize = test.size();
        for (int i = 0; i <= floor((float)test.size()/2)+1; i++) {
            ll newMax = min(bigtree.query(1, 0, newSize-1, 0, i-1), min(smalltree.query(1, 0, newSize-1, i+1, newSize-1), bigtree.query(1, 0, newSize-1, i+1, newSize-1)));
            ll curMin = small[i];
            ans = min(ans, (mx-curMin)*(newMax-mn));
        }
    }

    cout << ans << endl;
}