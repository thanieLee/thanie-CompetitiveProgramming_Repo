#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;



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
    void update(int v, int tl, int tr, int pos, pll val) {
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
    pll query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return pll(1000000, 1000000);
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};  

vector<pll> arr;
vector<vector<int>> adj;
vector<int> depth;
vector<int> start, en;
int timer = 0;
void dfs(int u, int p, ll dep) {
    arr.push_back({dep, u});
    start[u] = arr.size()-1;
    depth[u] = dep;

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, dep+1);
            arr.push_back({dep, u});
        }
    }
    en[u] = arr.size()-1;
}


int main(){
    int n, q; cin >> n >> q;
    adj.resize(n, vector<int>());
    start.resize(n, -1);
    en.resize(n, -1); 
    depth.resize(n, -1);

    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1, 0);
    segtree t(arr, arr.size());
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b; a--; b--;
        ll fir = start[a], sec = en[b];
        if (fir > sec) swap(fir, sec);
        cout << depth[a]+depth[b] - 2*depth[t.query(1, 0, arr.size()-1, fir, sec).second] << endl;
    }

}