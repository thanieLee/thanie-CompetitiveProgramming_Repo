#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<vector<ll>> dp;
vector<bool> isChild;
int n; 
ll solve(ll len, vector<vector<ll>> &adj){
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        vector<ll> counts(len);
        for (int j = 1; j < n; j++){
            for (ll child : adj[i]) {
                counts[j] += dp[child][j];
            }
        }
        cout << i << " " << len << endl;
        cout << "test: ";
        for (int i = 0 ; i < counts.size(); i++){
            cout << counts[i] << " "; 
        }
        cout << endl;
    }
    return ans;
}

int main(){
    cin >> n;
    vector<ll> tree(n+1);
    tree[0] = 0;
    isChild.resize(n+1, true);
    isChild[0] = false;
    vector<vector<ll>> graph(n+1, vector<ll>());
    for (int i = 0; i < n-1; i++){
        int pi; cin >> pi;
        tree[i] = pi;
        isChild[pi] = false;
        graph[pi].push_back(i+1);
    }


    dp.resize(n+1, vector<ll>(n+1, 0));
    for (int i = 0; i < n; i++){
        dp[i][1] = 1;
        dp[i][0] = 1;
    }
    
    cout << "test" << endl;
    cout << solve(1, graph) << endl;
    cout << solve(2, graph) << endl;
    cout << solve(3, graph) << endl;
    cout << solve(4, graph) << endl;
    cout << solve(5, graph) << endl;
    cout << dp[0][1] << endl;
}