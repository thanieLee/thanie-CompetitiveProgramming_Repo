#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll ,ll> pll;


struct segtree {
    vector<pll> t;
    int n;

    segtree(vector<pll> &a, int n) : n(n) {
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }
    void build(vector<pll> &a, int v, int tl, int tr) {
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
            t[v] = {val, pos};
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, val);
            else
                update(v*2+1, tm+1, tr, pos, val);
            
            pull(v);
        }
    }
    pll query(int v, int tl, int tr, int l, int r) {
        if (l <= tl and tr <= r)
            return t[v];
        int tm = (tl + tr) / 2;
        
        pll ans = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() };
        if (l <= tm) {
            ans = min(ans, query(2*v, tl, tm, l, r));
        }
        if (r > tm) {
            ans = min(ans, query(2*v+1, tm+1, tr, l, r));
        }
        return ans;
    }
};

int main(){
    int n; cin >> n;

    vector<pll> a;
    vector<int> frogs;
    for (int i = 0; i < 2e6+2; i++){
        a.push_back({0, i});
    }

    for (int i = 0; i < n; i++){
        int ni; cin >> ni;
        frogs.push_back(ni-1);
        a[ni-1].first=1;
    }


    segtree t(a, 2e6+2);
    //cout << t.query(1, 0, 2e6+2, 0, 2).first << " " << t.query(1, 0, 2e6+2, 0, 2).second << endl;

    int q; cin >> q;
    for (int i = 0; i < q; i++){
        int qi; cin >> qi;
        pll next = t.query(1, 0, 2e6+1, frogs[qi-1]+1, 2e6+2);
        t.update(1, 0, 2e6+1, frogs[qi-1], 0);
        t.update(1, 0, 2e6+1, next.second, 1);
        cout << next.second+1 << endl;
        frogs[qi-1] = next.second;
    }
}