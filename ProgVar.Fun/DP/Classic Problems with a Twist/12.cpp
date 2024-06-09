#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll MOD = 1000000007;

int main(){
    ll n, m; cin >> n >> m;
    vector<ll> dp(n+1, 0);
    vector<bool> can(n+1, true);

    for (int i = 0; i < m; i++) {
        ll ai; cin >> ai;
        can[ai] = false;
    }
    dp[0] = 1;
    if (can[1]) {
        dp[1] = 1;
    }

    for (int i = 2; i <= n; i++) {
        if (!can[i]) continue;

        if (can[i-1]) {
            dp[i] += dp[i-1];
            dp[i] %= MOD;
        }

        if (can[i-2]) {
            dp[i] += dp[i-2];
            dp[i] %= MOD;
        }
    }

    cout << dp[n] << endl;
}