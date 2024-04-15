#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<vector<int>> dp(n, vector<int>(4, 1000));
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr.push_back(x);
    }

    dp[0][0] = 1;
    for (int i = 0; i < 2; i++) {
        if (arr[0] & (1<<i)) {
            dp[0][1<<i] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int cur = arr[i];
        dp[i][0] = min(dp[i-1][0], min(dp[i-1][1], dp[i-1][2]))+1;
        if (cur & (1)) {
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]);
        } 
        if (cur & (2)) {
            dp[i][2] = min(dp[i-1][0], dp[i-1][1]);
        }
    }
    int ans = 1000;
    for (int i = 0; i < 3; i++) {
        ans = min(ans, dp[n-1][i]);
    }
    cout << ans << endl;
}