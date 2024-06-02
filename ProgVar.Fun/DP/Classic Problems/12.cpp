#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    string first, second;

    while (getline(cin, first)){
        getline(cin, second);
        int n = first.size(), m = second.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1));
        int ans = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 or j == 0) {
                    dp[i][j] = 0;
                } else if (first[i-1] == second[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        cout << dp[n][m] << endl;
    }
}