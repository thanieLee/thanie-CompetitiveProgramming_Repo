#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


struct Perm {
    vector<bool> a;

    Perm() {
        a.resize(26, false);
    }

    int cnt() {
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            if (a[i]) ans++;
        }
        return ans;
    }

    Perm operator+ (Perm B) {
        Perm sum = Perm();
        for (int i = 0; i < 26; i++) {
            sum.a[i] = a[i] or B.a[i];
        }
        return sum;
    }
};

struct segtree {
    vector<Perm> t;
    int n;

    segtree(vector<Perm> &a, int n) : n(n) {
        t.resize(4*n);
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
        t[v] = t[v*2] + t[v*2+1];
    }
    void update(int v, int tl, int tr, int pos, Perm val) {
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
    Perm query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return Perm();
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm)) + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    int n; cin >> n;
    string s; cin >> s;
    int q; cin >> q;

    vector<Perm> cur(n);
    for (int j = 0; j < n; j++) {
        Perm cu;
        cu.a[alpha.find(s[j])] = true;
        cur[j] = cu;
    }

    segtree tree(cur, n);
    

    for (int i = 0; i < q; i++) {
        int t; cin >> t; 
        if (t == 1) {
            int j; char c; cin >> j >> c; j--;
            Perm cu;
            cu.a[alpha.find(c)] = true;
            tree.update(1, 0, n-1, j, cu);
            s[j] = c; 
        } else {
            int l, r; cin >> l >> r; l--; r--; 
            cout << tree.query(1, 0, n-1, l, r).cnt() << "\n";
        }
    }
}