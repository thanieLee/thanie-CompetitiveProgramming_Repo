#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef long long int ll;
typedef vector<ll> vi;

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
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<ll> a(n+1, 1000000);
    segtree t(a, n+1);
    t.update(1, 0, n, 0, 0);

    for (int i = 1; i <= n; i++){
        if (s[i] == '1') continue;
        ll temp = t.query(1, 0, n, max(0, i-m), i);
        t.update(1, 0, n, i, temp+1);
    }
    
    ll len = t.query(1, 0, n, n, n);
    if (len > 100000) {
        cout << -1 << endl;
        return 0;
    }


    ll cur = n;
    deque<ll> test;
    while (cur != 0) {
        for (int i = cur-m; i < cur; i++){
            if (i < 0) continue;
            if (t.query(1, 0, n, i, i) == len-1){
                test.push_front(cur-i);
                len--;
                cur = i;
                break;
            }
        }
    }

    while (!test.empty()){
        cout << test.front() << " ";
        test.pop_front();
    }

}
