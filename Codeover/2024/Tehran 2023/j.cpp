#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<ll, ll> pll;

struct rmq {
    int n, *vals, *deltas;
    rmq(vector<int> ar) {
        n = ar.size();
        vals = new int[4*n];
        deltas = new int[4*n];
        build(ar, 1, 0, n-1);
    }
    
    void build(vector<int> ar, int p, int i, int j) {
        deltas[p] = 0;
        if (i == j) {
            vals[p] = ar[i];
        }
        else {
            int k = (i + j) / 2;
            build(ar, p<<1, i, k);
            build(ar, p<<1|1, k+1, j);
            pull(p);
        }
    }
    
    void pull(int p) {
        vals[p] = min(vals[p<<1], vals[p<<1|1]);
    }

    void push(int p, int i, int j) {
        if (deltas[p]) { 
            vals[p] += deltas[p];
            if (i != j) {
                deltas[p<<1] += deltas[p];
                deltas[p<<1|1] += deltas[p];
            }
            deltas[p] = 0;
        }
    }

    // i, j starts at 0, n-1
    void update(int _i, int _j, int v, int p, int i, int j) {
        push(p, i, j);
        // query overlaps or equates i, j
        if (_i <= i && j <= _j) {
            deltas[p] += v;
            push(p, i, j);
        }
        // no overlap
        else if (_j < i || j < _i) {}
        else {
            int k = (i + j) / 2;
            update(_i, _j, v, p<<1, i, k);
            update(_i, _j, v, p<<1|1, k+1, j);
            pull(p);
        }
    }

    int query(int _i, int _j, int p, int i, int j) {
        push(p, i, j);
        if (_i <= i && j <= _j)
            return vals[p];
        else if (_j < i || j < _i)
            return 1000000000;
        else {
            int k = (i + j) / 2;
            return  min(query(_i, _j, p<<1, i, k),
                    query(_i, _j, p<<1|1, k+1, j));
        }
    }

    void update(int _i, int _j, int v) {
        update(_i, _j, v, 1, 0, n-1);
    }

    int query(int _i, int _j) {
        return query(_i, _j, 1, 0, n-1);
    }
};

bool cmp(pll &x, pll &y) {
    if (x.first == y.first) {
        x.second > y.second;
    }
    return x.first > y.first;
}
                                                       
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, k; cin >> n >> k;
    vector<pll> why;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        why.push_back({x, i});
    }

    vector<ll> te(n, 0);
    rmq t(te);
    vector<ll> ans(n, n+1000);
    sort(why.begin(), why.end(), cmp);
    vector<pll> queries;
    ll prev = why[0].first;
    queue<pll> que;
    for (pll p : why){
        ll i = p.second;
        ll val = p.first;
        if (val != prev) {
            while (!que.empty()) {
                auto cur = que.front();
                que.pop();
                t.update(cur.first, cur.second, 1);
            }
            prev = val;
        }
        ll l = max(0, i-k+1);
        ll r = min(n-k, i);
        ans[i] = t.query(l, r);
        que.push({l, r});
    }
    // for (auto it = test.rbegin(); it != test.rend(); it++) {
    //     vector<pll> queries;
        
    //     for (auto i : it->second) {

    //         ll l = max(0, i-k+1);
    //         ll r = min(n-k, i);
    //         queries.push_back({l, r});
    //         //cout << it->first << " " << l << " " << r << endl;
    //         ll cur_ans = t.query(1, 0, n-1, l, r);
    //         ans[i] = cur_ans;
    //     }
    //     for (auto q : queries) {
    //         t.update(1, 0, n-1, q.first, q.second, 1);
    //     }
    //     // vector<pll> final_queries;
    //     // for (int i = 0; i < queries.size(); i++) {
    //     //     if (i == queries.size()-1) {
    //     //         final_queries.push_back(queries[i]);
    //     //     } else {
    //     //         pll cur_query = queries[i];
    //     //         while (queries[i].second > queries[i+1].first) {
    //     //             cur_query.second = queries[i+1].second;
    //     //             i++;
    //     //             if (i == queries.size()-1) {
    //     //                 if (queries[i].first < cur_query.second) {
    //     //                     cur_query.second = queries[i].second;
    //     //                 }
    //     //                 break;
    //     //             }
    //     //         }
    //     //         final_queries.push_back(cur_query);
    //     //     }
    //     // }

    //     // for (auto f_q : final_queries) {
    //     //     t.update(1, 0, n-1, f_q.first, f_q.second, 1);
    //     // }

    // }

    for (ll i = 0; i < n; i++) {
        cout << ans[i]+1 << " ";
        
    }

    cout << endl;
}