#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

void dfs(ll u, ll p, ll& dfsCnt, vector<ll> dfsArr, vector<bool> &vis, vector<set<pll>> &adj) {
    vis[u] = true;

    for (auto v : a)
}



int main(){
    int n; cin >> n;
    vector<ll> a;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        a.push_back(x);
    }
    int c; cin >> c;
    vector<pll> swaps;
    vector<set<pll>> adj(n, set<pll>());
    for (int i = 0; i < c; i++) {
        ll a, b; cin >> a >> b;
        if (a > b) swap(a, b);
        swaps.push_back({a, b});
        adj[a].insert({b, i});
        adj[b].insert({a, i});
    }


}

