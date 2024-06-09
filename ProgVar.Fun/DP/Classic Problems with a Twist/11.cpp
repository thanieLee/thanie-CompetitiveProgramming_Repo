#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    ll n, m; cin >> n >> m;
    ll INF = 1000000000000000000;
    vector<vector<ll>> arrs(n);
    vector<int> sizes(n);

    for (int i = 0; i < n; i++) {
        int size; cin >> size;
        vector<ll> cur(size);
        sizes[i] = size;

        for (int j = 0; j < size; j++) {
            ll ai; cin >> ai;
            cur[j] = ai;
        }

        arrs[i] = cur;
    }

    vector<int> idxs;
    for (int i = 0; i < m; i++) {
        int mi; cin >> mi;
        idxs.push_back(mi);
    }

    vector<ll> maxPref(n, -INF), whole(n, 0), maxSuff(n, -INF);
    for (int i = 0; i < n; i++) {
        ll cur = 0;
        for (int j = 0; j < sizes[i]-1; j++) {
            cur += arrs[i][j];
            maxPref[i] = max(maxPref[i], cur);
        }
        cur = 0;
        for (int j = sizes[i]-1; j > 0; j--) {
            cur += arrs[i][j];
            maxSuff[i] = max(maxSuff[i], cur);
        }
        cur += arrs[i][0];
        whole[i] = cur;
    }


    vector<vector<ll>> dp(m+1, vector<ll>(3, -INF));
    for (int i = 0; i < 3; i++) {
        dp[0][i] = 0;
    }

    ll ans = -INF;
    for (int j = 1; j <= m; j++) {
        int curr = idxs[j-1];
        dp[j][0] = max(maxPref[curr-1], max(dp[j-1][1]+maxPref[curr-1], dp[j-1][2]+maxPref[curr-1]));
        dp[j][1] = max(whole[curr-1], max(dp[j-1][1]+whole[curr-1], dp[j-1][2]+whole[curr-1]));
        dp[j][2] = maxSuff[curr-1];
        ans = max(ans, dp[j][0]);
        ans = max(ans, dp[j][1]);
        ans = max(ans, dp[j][2]);
    }
    vector<ll> tempANS(n, -INF);
    for (int i = 0; i < n; i++) {
        vector<ll> curDP(sizes[i]+1, -INF);
        curDP[0] = 0;
        ll curANS = -INF;
        for (int j = 0; j < sizes[i]; j++) {
            curDP[j+1] = max(curDP[j]+arrs[i][j], arrs[i][j]);
            curANS = max(curDP[j+1], curANS);
        }
        tempANS[i] = curANS;
    }

    for (int i = 0; i < m; i++) {
        ans = max(ans, tempANS[idxs[i]-1]);
    }
    
    cout << ans << endl;
}