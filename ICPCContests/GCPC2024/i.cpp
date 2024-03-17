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
    void update(int index, int value, int position = 1, int currentL = 0, int currentR = 2e6+1) {
        if (currentL == currentR) {
            t[position] = { value, index };
            return;
        }
        int mid = (currentL+currentR)/2;
        if (index <= mid) {
            update(index, value, position*2, currentL, mid);
        } else {
            update(index, value, position*2+1, mid+1, currentR);
        }
        pull(position);
    }

    std::pair<int, int> query(int qL, int qR, int c = 1, int cL = 0, int cR = 2e6+1) {
        if (qL <= cL && cR <= qR) {
            return t[c];
        }
        int mid = (cL+cR)/2;
        std::pair<int, int> ans = { std::numeric_limits<int>::max(), std::numeric_limits<int>::max() };
        if (qL <= mid) {
            ans = min(ans, query(qL, qR, 2*c, cL, mid));
        }
        if (qR > mid) {
            ans = min(ans, query(qL, qR, 2*c+1, mid+1, cR));
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
        pll next = t.query(frogs[qi-1]+1, 2e6+2);
        t.update(frogs[qi-1], 0);
        t.update(next.second, 1);
        cout << next.second+1 << endl;
        frogs[qi-1] = next.second;
    }
}