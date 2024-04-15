#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, m, c0, d0; cin >> n >> m >> c0 >> d0;
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    vector<vector<int>> arr;
    for (int i = 0; i < m; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        arr.push_back({a, b, c, d});
    }

    for (int k = 0; k <= n; k++) {
        vector<int> cur = arr[0];
        if (k*cur[2] <= n and cur[0] - k*cur[1] >= 0) {
            dp[k*cur[2]][0] += cur[3]*k;

        }
    }

    for (int i = 1; i < m; i++) {
        for (int j = n; j >= 0; j--) {
            for (int k = 0; k <= n; k++) {
                vector<int> cur = arr[i];
                if (j + k*cur[2] <= n and cur[0] - k*cur[1] >= 0) {
                    dp[j + k*cur[2]][i] = max(dp[j + k*cur[2]][i], dp[j][i-1]+cur[3]*k);
                }
            }
        }
    }

    int ans = 0;
    for (int i = n; i >= 0; i--) {
        ans = max(ans, dp[i][m-1]+((n-i)/c0)*d0);
    }
    cout << ans << endl;
}