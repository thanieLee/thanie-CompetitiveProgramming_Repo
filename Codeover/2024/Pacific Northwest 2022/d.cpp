#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef pair<ld, ld> pld;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;

template <class T> struct cmp {
  bool operator() (const T& x, const T& y) const {
    if (x.second.second==y.second.second) return x.first.first < y.first.first;
    return x.second.second<y.second.second;
  
  }
  typedef T first_argument_type;
  typedef T second_argument_type;
  typedef bool result_type;
};
 
typedef tree<pair<pll, pld>, null_type, cmp<pair<pll, pld>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

bool cmp1(pair<pll, pld> x, pair<pll, pld> y) {
    return x.second.first < y.second.first;
}

bool cmp2(pair<pll, pld> x, pair<pll, pld> y) {
    return x.second.second < y.second.second;
}

ld dot(pld x, pld y) {
    return x.first*y.first + x.second*y.second;
}

ld dist(pld x, pld y) {
    return sqrt(pow(x.first-y.first, 2) + pow(x.second-y.second, 2));
}

pld diff(pld x, pld y) {
    return {x.first-y.first, x.second-y.second};
}
ld angle(pld p1, pld p2) {
    ld x1 = p1.first;
    ld x2 = p2.first;
    ld y1 = p1.second;
    ld y2 = p2.second;
    ld dot = x1*x2 + y1*y2; 
    ld det = x1*y2 - y1*x2;     
    ld angle = atan2(det, dot);
    if (angle < 0)
        angle *= -1;
    return angle;
}

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
    vector<pld> points;
    vector<pair<pll, pld>> angles;
    int n; ld x; cin >> n >> x;
    pld left_base = {0, 0};
    pld right_base = {x, 0};
    vector<ll> values;

    for (int i = 0; i < n; i++) {
        ld xi, yi; ll vi; cin >> xi >> yi >> vi;
        values.push_back(vi);
        points.push_back({xi, yi});
        angles.push_back({{i, -1ll}, {angle(diff(right_base, left_base), diff({xi, yi}, left_base)), angle(diff(left_base, right_base), diff({xi, yi}, right_base))}});
        //cout << angles[i].second.first << " " << angles[i].second.second << endl;
    }

    sort(angles.begin(), angles.end(), cmp1);
    for (int i = 0; i < n; i++) {
        angles[i].first.second = i;
    }

    sort(angles.begin(), angles.end(), cmp2);
    vector<ll> idx_conv(n);

    for (int i = 0; i < n; i++) {
        idx_conv[angles[i].first.second] = i;
    }

    sort(angles.begin(), angles.end(), cmp1);
    vector<ll> val(n+1, 0);
    segtree t(val, n+1);
    ordered_multiset active;
    vector<ll> ans(n, 0);
    for (int i = 0; i < n; i++) {
        ans[angles[i].first.first] = t.query(1, 0, n, 0, idx_conv[i]+1);
        t.update(1, 0, n, idx_conv[i]+1, values[angles[i].first.first]);
        active.insert(angles[i]);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
} 