#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define INF 1000000000ll


int main(){
    ll n, m; cin >> n >> m;
    vector<ll> a, b;
    vector<int> c;
    vector<vector<ll>> dp(m+2, vector<ll>((1<<n), INF));
    for (int i = 0; i < m; i++){
        ll ai, bi; cin >> ai >> bi;
        int cBit = 0;
        for (int j = 0; j < bi; j++){
            ll cbii; cin >> cbii;
            cBit |= (1<<(cbii-1));
        }
        c.push_back(cBit);
        a.push_back(ai);
        b.push_back(bi);
    }

    for (int i = 1; i <= m; i++){
        dp[i][c[i-1]] = min(a[i-1], dp[i][c[i-1]]);

        for (int j = 1; j < (1<<n); j++){
            dp[i][j] = min(dp[i-1][j], dp[i][j]);
            dp[i][j|c[i-1]] = min(dp[i-1][j] + a[i-1], dp[i][j|c[i-1]]);
            dp[i][j] = min(dp[i-1][j], dp[i][j]);

        }
    }

    if (dp[m][(1<<n)-1] == 1000000000) {
        cout << -1 << endl;
    } else {
        cout << dp[m][(1<<n)-1] << endl;
    }
}