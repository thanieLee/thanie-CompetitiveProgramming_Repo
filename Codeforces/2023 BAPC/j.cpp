#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MOD 1000000007

int mod(ll x){
    return ((x%MOD)+MOD)%MOD;
}


int main(){
    ll n; cin >> n;
    vector<vector<int>> adj(n, vector<int>());
    vector<int> parent(n, 0);

    for (int i = 1; i < n; i++){
        int pi; cin >> pi;
        adj[pi].push_back(i);
        parent[i] = pi;
    }

    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n+1, vector<int>()));
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= n; j++) {
            dp[i][j].resize(adj[i].size()+1, 0);
        }
    }
    deque<int> q, order;
    q.push_back(0);
    while(!q.empty()){
        int cur = q.front();
        order.push_front(cur);
        q.pop_front();
        for (int v : adj[cur]) {
            q.push_back(v);
        }
    }

    vector<int> size(n, 1);

    deque<int> orderCopy = order;

    while (!orderCopy.empty()){
        for (int v : adj[orderCopy.front()]){
            size[orderCopy.front()] += size[v];
        }
        orderCopy.pop_front();
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < dp[i][0].size(); j++){
            dp[i][0][j] = 1;
        }
    }


    while (!order.empty()) {
        int cur = order.front();
        order.pop_front();
        if (adj[cur].size() == 0) {
            dp[cur][0][0] = 1;
            dp[cur][1][0] = 1; 
        } else {
            for (int i = 0; i < n; i++) {
                dp[cur][i+1][1] = dp[adj[cur][0]][i][dp[adj[cur][0]][i].size()-1];
            }
            for (int i = 2; i < adj[cur].size()+1; i++){
                for (int j = 0; j <= n; j++){
                    for (int k = 0; k <= min(size[adj[cur][i-1]], j-1); k++){
                        dp[cur][j][i] += mod(1LL * dp[adj[cur][i-1]][k][dp[adj[cur][i-1]][k].size()-1]*dp[cur][j-k][i-1]);
                        dp[cur][j][i] = mod(dp[cur][j][i]);
                    }
                }
            }
        }
    }


    for (int i = 1; i <= n; i++){
        ll ans = 0;
        for (int j = 0; j < n; j++){
            ans += dp[j][i][dp[j][i].size()-1];
            ans %= MOD;
        }   
        cout << ans%MOD << '\n';
    }
}