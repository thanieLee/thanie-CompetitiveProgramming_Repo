#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef vector<int> vi;
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

int main(){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<int, int>> val;
     double time_taken;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        val.push_back({x, i});
    }
    sort(val.begin(), val.end());
    vector<int> compressed(n, -1);
    for (int i = 0; i < n; i++){
        compressed[val[i].second] = i;
    }

    
    vector<ll> ans(n, 0);
    vector<ll> arr(n, 0);
    segtree t(arr, n);

    for (int i = n-1; i >= 0; i--) {
        ll cnt = 0;
        cnt += t.query(1, 0, n-1, 0, compressed[i]);
        t.update(1, 0, n-1, compressed[i], 1);
        ans[i] = cnt;
    }

    vector<ll> test(n, 0);
    segtree t1(test, n);
    ll out = 0;

    for (int i = n-1; i >= 0; i--){
        out += t1.query(1, 0, n-1, 0, compressed[i]);
        t1.update(1, 0, n-1, compressed[i], ans[i]);
    }
    cout << out << endl;








}