#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m = 3;
    ll MOD = 1000000007;
    cin >> n;
    while (n != -1) {
        ll full = (1<<(m+1)) - 1;
        vector<vector<vector<ll>>> dp(n+2, vector<vector<ll>>(m+2, vector<ll>((1<<(m+2)), 0)));
        dp[0][m][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int msk = 0; msk <= full; ++msk) {
                dp[i][0][msk<<1] += dp[i-1][m][msk] % MOD;
            }

            for (int j = 1; j <= m; ++j) {
                for (int msk = 0; msk <= full; ++msk) {
                    ll right = msk & (1 << (j-1)), down = msk & (1 << (j));


                    if (!right and !down){
                        dp[i][j][msk ^ (1 << j)] += dp[i][j - 1][msk]% MOD;
                        dp[i][j][msk ^ (1 << (j - 1))] += dp[i][j - 1][msk]% MOD;
                    } else if (right and !down){
                        dp[i][j][msk ^ (1 << (j - 1))] += dp[i][j - 1][msk]% MOD;
                    } else if (!right and down){
                        dp[i][j][msk ^ (1 << j)] += dp[i][j - 1][msk]% MOD;
                    }
                }
            }
        }
        cout << dp[n][m][0]% MOD << endl;
        cin >> n;
    }
}