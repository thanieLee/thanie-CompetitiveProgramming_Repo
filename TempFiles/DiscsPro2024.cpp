#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct Perm{
    int n;
    vector<int> a;
    Perm() {

    }
    Perm(int n) : n(n) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i] = i;
        }
    }

    Perm operator* (Perm B) {
        Perm product = Perm(n);
        for (int i = 0; i < n; i++) {
            product.a[i] = a[B.a[i]];
        }
        return product;
    }
};

struct segtree {
    vector<Perm> t;
    int n, m;
    
    segtree(vector<Perm> &a, int n, int m1) : n(n) {
        t.resize(4*n);
        m = m1;
        build(a, 1, 0, n-1);
    }
    void build(vector<Perm> &a, int v, int tl, int tr) {
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
        t[v] = t[v*2]*t[v*2+1];
    }
    void update(int v, int tl, int tr, int pos, Perm &per) {
        if (tl == tr) {
            t[v] = per;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, per);
            else
                update(v*2+1, tm+1, tr, pos, per);
            
            pull(v);
        }
    }

    Perm query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return Perm(m);
        if (l <= tl and tr <= r)
            return t[v];
        int tm = (tl + tr) / 2;
        
        Perm ans = query(2*v, tl, tm, l, min(r, tm))*query(2*v+1, tm+1, tr, max(l, tm+1), r);
        return ans;
    }
};
using namespace std::chrono;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto start = high_resolution_clock::now();
    int n, m; cin >> n >> m;
    vector<Perm> permutations;
    Perm sta(m);
    for (int i = 0; i < m; i++) {
        ll x; cin >> x; x--;
        sta.a[i] = x;
    }
    for (int i = 0; i < n; i++) {
        Perm cur(m);
        int l, r; cin >> l >> r; l--; r--;
        cur.a[l] = r;
        cur.a[r] = l;
        permutations.push_back(cur);
    }
    segtree t(permutations, n, m);
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        string query; cin >> query;
        if (query == "PERM") {
            int l, r; cin >> l >> r; l--; r--;
            Perm ans = sta*t.query(1, 0, n-1, l, r);
            for (int i = 0; i < m; i++){
                cout << ans.a[i]+1 << " ";
            }
            cout << '\n';
        } else {
            int pos, l, r; cin >> pos >> l >> r; pos--; l--; r--;
            Perm next(m);
            next.a[l] = r;
            next.a[r] = l;
            t.update(1, 0, n-1, pos, next);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
}