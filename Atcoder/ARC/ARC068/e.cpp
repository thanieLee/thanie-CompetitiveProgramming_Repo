#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct segtree {
    vector<ll> t, ladd, lset;
    int n;

    segtree(vector<ll> &a, int n) : n(n) {
        t.resize(4*n);
        ladd.resize(4*n, 0);
        lset.resize(4*n, 0);
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
    void push(int v, int tl, int tr) {
            if (lset[v]) {
                if (tl != tr) {
                    lset[v*2] = lset[v*2+1] = lset[v];
                    ladd[v*2] = ladd[v*2+1] = 0;
                }
                t[v] = (tr - tl + 1) * lset[v];
                lset[v] = 0;
            } 
            if (ladd[v]) {
                t[v] += (tr - tl + 1) * ladd[v];

                if (tl != tr) {
                    ladd[v*2] += ladd[v];
                    ladd[v*2+1] += ladd[v];
                }
                
                ladd[v] = 0;
            }
    }
    void increment(int v, int tl, int tr, int l, int r, ll val) {
        push(v, tl, tr);
        if (l > r)
            return;
        if (l == tl and r == tr) {
            ladd[v] += val;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr)/2;
            increment(v*2, tl, tm, l, min(r, tm), val);
            increment(v*2+1, tm+1, tr, max(l, tm+1), r, val);
            pull(v);
        }
    }
    void set(int v, int tl, int tr, int l, int r, ll val) {
        push(v, tl, tr);
        if (l > r)
            return;
        if (l == tl and r == tr) {
            lset[v] = val;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            set(v*2, tl, tm, l, min(r, tm), val);
            set(v*2+1, tm+1, tr, max(l, tm+1), r, val);
            pull(v);
        }
    }


    ll query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr);
        if (l > r)
            return 0;
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm)) + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};

bool cmp1(pair<int, int> &x, pair<int, int> &y){
    if (x.first == y.first) {
        return x.second < y.second;
    }
    return x.first < y.first;
}

bool cmp2(pair<int, int> &x, pair<int, int> &y){
    return (x.second-x.first) < (y.second-y.first);
}

int main(){
    int n, m; cin >> n >> m;
    vector<pair<int, int>> intervals;

    for (int i = 0; i < n; i++){
        int li, ri; cin >> li >> ri;
        intervals.push_back({li, ri});
    }

    sort(intervals.begin(), intervals.end(), cmp2);
    vector<ll> lines(m+1, 0);
    segtree t(lines, m+1);
    int idx = 0;
    for (int i = 1; i <= m; i++){
        int cnt = 0;
        if (idx < n) {
            while (intervals[idx].second-intervals[idx].first+1 < i) {
                t.increment(1, 0, m, intervals[idx].first, intervals[idx].second, 1);
                idx++;
                if (idx == n) break;
            }
        }

        for (int j = i; j <= m; j += i){
            cnt += t.query(1, 0, m, j, j);
        }

        cnt += n-idx;
        cout << cnt << endl;
    }


}