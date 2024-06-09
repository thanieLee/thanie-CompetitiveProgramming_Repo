#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll h, n; cin >> h >> n;
    vector<ll> dmg, cost;
    ll INF = 10000000000;
    for (int i = 0; i < n; i++) {
        ll ai, bi; cin >> ai >> bi;
        dmg.push_back(ai);
        cost.push_back(bi);
    }

    vector<ll> dp(h+1, INF);
    dp[h] = 0;
    for (int i = h; i >= 1; i--) {
        for (int j = 0; j < n; j++) {
            dp[max(0ll, i-dmg[j])] = min(dp[max(0ll, i-dmg[j])], dp[i]+cost[j]);

        }
    }
    cout << dp[0] << endl;
}