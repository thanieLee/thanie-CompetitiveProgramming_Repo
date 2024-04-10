#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll n, m, k, x;

int main(){
    cin >> n >> m;
    vector<vector<ll>> adj(n, vector<ll>());
    for (int i = 0; i < n-1; i++){
        ll u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> k >> x;
    deque<ll> order;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            order.push_back(i);
        }
    }
    deque<ll> q = order;
    vector<bool> vis(n, false);
    while(!q.empty()) {
        ll cur = q.front();
        q.pop_front();
        vis[cur] = true;

        for (auto v : adj[cur]) {
            if (!vis[v]) {
                q.push_back(v);
                order.push_back(v);
                vis[v] = true;
            }
        }
    }

    ll root = order.back();
    vis.clear();
    vis.resize(n, false);
    vector dp(n, vector(x+1, vector<ll>(3, 0)));

    for (int i = 0; i < n; i++) {
    while (!order.empty()) {
        ll cur = order.front();
        order.pop_front();
        vis[cur] = true;

        if (adj[cur].size() == 1) {

        } else {
            for (auto v : adj[cur]) {
                if (vis[v]) {
                    
                }
            }
        }
    }

}