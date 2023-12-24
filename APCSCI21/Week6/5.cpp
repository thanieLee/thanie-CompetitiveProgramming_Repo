#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

void dijkstra(int src, vector<int>& dist, vector<bool> &done, vector<vector<pair<int, int>>> &adj) {
    dist[src] = 0;
    set<pair<ll, int>> q;
    q.insert({dist[src], src});

    while (q.size() > 0) {
        int u = (*q.begin()).second; q.erase(q.begin());

        if (!done[u]) {
            for (auto e : adj[u]) {
                int v = e.second;
                ll w = e.first;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    q.insert({dist[v], v});
                }
            }
            done[u] = true;
        }
    }
}

int main(){
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(2*n+1, vector<pair<int, int>>());

    for (int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c; a--; b--;
        adj[a].push_back({c, b+n});
        adj[a].push_back({c, b});
    }

    for (int i = 0; i < n; i++){
        vector<bool> done(2*n+1, false);
        vector<int> dist(2*n+1, 1000000000);
        dijkstra(i, dist, done, adj);
       if (dist[i+n] == 1000000000){
        cout << -1 << endl;
       } else {
        cout << dist[i+n] << endl;
       }
    }
}
