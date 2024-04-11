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

int main() {
    int T; cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;
        string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        map<char, int> idx;
        for (int i = 0; i < 26; i++) {
            idx[alpha[i]] = i; 
        }

        vector<segtree> segs;
        for (int i = 0; i < 26; i++) {
            vector<ll> cur(n, 0);
            segtree yes(cur, n);
            segs.push_back(yes);
        }
        string s; cin >> s;
        vector<char> stringVec(n, ' ');
        for (int i = 0; i < s.size(); i++) {
            segs[idx[s[i]]].update(1, 0, n-1, i, 1);
            stringVec[i] = s[i];
        }

        for (int i = 0; i < q; i++) {
            string query; cin >> query;
            if (query == "SWAP") {
                int l, r; cin >> l >> r; l--; r--;
                int c1 = stringVec[l], c2 = stringVec[r];
                stringVec[l] = c2;
                stringVec[r] = c1;

                segs[idx[c1]].update(1, 0, n-1, l, 0);
                segs[idx[c2]].update(1, 0, n-1, r, 0);
                segs[idx[c1]].update(1, 0, n-1, r, 1);
                segs[idx[c2]].update(1, 0, n-1, l, 1);
            } else {
                char c; cin >> c;
                int l, r; cin >> l >> r; l--; r--;
                cout << segs[idx[c]].query(1, 0, n-1, l, r) << " ";
            }
        }
        cout << endl;
    }
}