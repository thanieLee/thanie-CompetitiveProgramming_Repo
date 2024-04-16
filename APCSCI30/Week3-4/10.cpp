#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll n, m, k, x;
vector<vector<vector<ll>>> dp(100010, vector<vector<ll>>(3, vector<ll>(20)));
vector<vector<ll>> node(3, vector<ll>(12));
ll MOD = 1000000007ll;

ll mod(ll x) {
    return ((x%MOD)+MOD)%MOD;
}

void dfs(ll u, ll p, vector<vector<ll>> &adj) {
    if (adj[u].size() == 1 and p != 0) {
        dp[u][0][0] = k-1;
        dp[u][1][1] = 1;
        dp[u][2][0] = m-k;
    } else {
        dp[u][0][0] = k-1;
        dp[u][1][1] = 1;
        dp[u][2][0] = m-k;
        for (ll v: adj[u]) {
            if (v != p) {
                dfs(v, u, adj);
            }
        }


        for (ll v : adj[u]) {
            if (v == p) continue;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j <= x; j++) {
                    node[i][j] = 0;
                }
            }
            for (int i = 0; i <= x; i++) {
                for (int j = 0; j <= x-i; j++) {
                    node[1][i+j] += mod(mod(dp[v][0][j])*dp[u][1][i]);
                    node[1][i+j] = mod(node[1][i+j]);
                    node[0][i+j] += mod(mod(dp[v][0][j] + dp[v][1][j] + dp[v][2][j])*dp[u][0][i]);
                    node[0][i+j] = mod(node[0][i+j]);
                    node[2][i+j] += mod(mod(dp[v][0][j] + dp[v][2][j])*dp[u][2][i]);
                    node[2][i+j] = mod(node[2][i+j]);
                } 
            }
            
            for (int i = 0; i  < 3; i++) {
                for (int j = 0; j <= x; j++){
                    dp[u][i][j] = node[i][j];
                }
            }
        }
    }
}


int main() {
    cin >> n >> m;
    vector<vector<ll>> adj(n+1, vector<ll>());
    for (int i = 0; i < n-1; i++) {
        ll ui, vi; cin >> ui >> vi;
        adj[ui].push_back(vi);
        adj[vi].push_back(ui);
    }
    cin >> k >> x;
    dfs(1, 0, adj);
    ll ans = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j <= x; j++) {
            ans += dp[1][i][j];
            //cout << dp[1][i][j] << " " << i << " " << j <<  endl;
            ans = mod(ans);
        }
    }
    cout << ans << endl;
}
