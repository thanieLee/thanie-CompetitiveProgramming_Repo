#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

struct segtree {
    vector<ll> t, lazy;
    int n;

    segtree(vector<ll> &a, int n) : n(n) {
        t.resize(4*n);
        lazy.resize(4*n, 0);
        build(a, 1, 0, n-1);
    }

    void build(vector<ll> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = max(t[v*2], t[v*2 + 1]);
        }
    }

    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r) 
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = max(t[v*2], t[v*2+1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return -10000000;
        if (l == tl && tr == r)
            return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return max(query(v*2, tl, tm, l, min(r, tm)), 
                query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};

struct segtree2 {
    vector<ll> t, lazy;
    int n;

    segtree2(vector<ll> &a, int n) : n(n) {
        t.resize(4*n);
        lazy.resize(4*n, 0);
        build(a, 1, 0, n-1);
    }

    void build(vector<ll> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = min(t[v*2], t[v*2 + 1]);
        }
    }

    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }

    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r) 
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = min(t[v*2], t[v*2+1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 10000000;
        if (l == tl && tr == r)
            return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm)), 
                query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};

                                                       


int main(){
    ll n, k; cin >> n >> k;
    map<ll, vector<ll>> test;
    vector<ll> a;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        if (test.find(x) == test.end()) {
            test[x] = {i};
        } else {
            test[x].push_back(i);
        }
        a.push_back(x);
    }

    vector<ll> te(n, 0);
    segtree2 t(te, n);
    vector<ll> ans(n, n+1000);
    for (auto it = test.rbegin(); it != test.rend(); it++) {
        vector<pll> queries;
        
        for (auto i : it->second) {

            ll l = max(0ll, i-k+1);
            ll r = min(n-k, i);
            queries.push_back({l, r});
            //cout << it->first << " " << l << " " << r << endl;
            ll cur_ans = t.query(1, 0, n-1, l, r);
            ans[i] = cur_ans;
        }
        for (auto q : queries) {
            t.update(1, 0, n-1, q.first, q.second, 1);
        }
        // vector<pll> final_queries;
        // for (int i = 0; i < queries.size(); i++) {
        //     if (i == queries.size()-1) {
        //         final_queries.push_back(queries[i]);
        //     } else {
        //         pll cur_query = queries[i];
        //         while (queries[i].second > queries[i+1].first) {
        //             cur_query.second = queries[i+1].second;
        //             i++;
        //             if (i == queries.size()-1) {
        //                 if (queries[i].first < cur_query.second) {
        //                     cur_query.second = queries[i].second;
        //                 }
        //                 break;
        //             }
        //         }
        //         final_queries.push_back(cur_query);
        //     }
        // }

        // for (auto f_q : final_queries) {
        //     t.update(1, 0, n-1, f_q.first, f_q.second, 1);
        // }

    }
    vector<ll> hmm(n, 1000000000);
    for (int i = 0; i < n-k+1; i++) {
        hmm[i] = t.query(1, 0, n-1, i, i);
        //cout << t.query(1, 0, n-1, i, i) << " ";
    }
    //cout << endl;



    for (ll i = 0; i < n; i++) {
        cout << ans[i]+1 << " ";
        
    }

    cout << endl;
}