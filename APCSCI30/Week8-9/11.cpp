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
            return 1000000;
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};

int main(){
    ll n, s, l; cin >> n >> s >> l;
    vector<ll> arr;
    for (int i = 0; i < n; i++){
        ll x; cin >> x;
        arr.push_back(x);
    }
    vector<ll> range(n, -1);
    ll idx = -1;
    multiset<ll> sli;
    deque<ll> q;

    for (int i = 0; i < n; i++){
        sli.insert(arr[i]);
        q.push_back(i);
        while (*sli.rbegin()-*sli.begin() > s) {
            sli.erase(sli.find(arr[q.front()]));
            q.pop_front();

            if (sli.empty()) break;
        }
        range[i] = q.front();
    }

    for (int i = 0; i < n ; i++){
        //cout << range[i] << " ";
    }
    //cout << endl;

    vector<ll> st(n, 1000000), en(n, 1000000);
    segtree start(st, n), end(en, n);
    start.update(1, 0, n-1, 0, 1);

    if (l == 1){
        end.update(1, 0, n-1, 0, 1);
    }
    

    for (int i = 1; i < n; i++){
        ll startIdx = range[i];
        ll endIdx = i-l+1;
        //cout << i << " " << startIdx << " " << endIdx << endl;
        if (end.query(1, 0, n-1, i-1, i-1) < 1000000){
            start.update(1, 0, n-1, i, end.query(1, 0, n-1, i-1, i-1)+1);
        }
        if (startIdx <= endIdx){
            ll mi = start.query(1, 0, n-1, startIdx, endIdx);
            if (mi < 1000000)
                end.update(1, 0, n-1, i, mi);
        }
    }

    ll ans = end.query(1, 0, n-1, n-1, n-1);
    if (ans < 1000000){
        cout << ans << endl;
    }  else {
        cout << -1 << endl;
    }
}