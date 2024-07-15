#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<ll, ll> pll;

vector<vector<pll>> dp;
vector<set<int>> dag_adj;
ll n, m, t, d;

ll dag_dp(int cur) {
    ll mx = 0;
    for (int v : dag_adj[cur]) {
        dp[v].push_back()
    }
}

int main(){
     cin >> n >> m >> t >> d;
    vector<bool> is_station(n, false);

    for (int i = 0; i < t; i++) {
        int xi; cin >> xi; xi--;
        is_station[xi] = true;
    }

    vector<vector<int>> dist(n, vector<int>(n, -1));
    vector<vector<int>> first_adj(n, vector<int>());
    
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c; a--; b--;
        dist[a][b] = c;
        dist[b][a] = c;
        first_adj[a].push_back(b);
        first_adj[b].push_back(a);
    }

    dag_adj.resize(n, set<int>());
    vector<vector<bool>> path(n, vector<bool>(n, false));

    deque<int> bfs = {0};
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop_front();

        for (int v : first_adj[cur]) {
            if (!path[v][cur]) {
                path[cur][v] = true;
                dag_adj[cur].insert(v);
                bfs.push_back(v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int v : dag_adj[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}