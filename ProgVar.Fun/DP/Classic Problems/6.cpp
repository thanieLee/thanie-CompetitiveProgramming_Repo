#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, x; cin >> n >> x;
    vector<int> price, pages;
    for (int i = 0; i < n; i++) {
        int hi; cin >> hi;
        price.push_back(hi);
    }

    for (int i = 0; i < n; i++) {
        int si; cin >> si;
        pages.push_back(si);
    }

    vector<vector<int>>  dp(1001, vector<int>(100001, 0));
    for (int i = 1; i <= n; i++)  {
        for (int j = 0; j <= x; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= price[i-1])
                dp[i][j] = max(dp[i][j], dp[i-1][j-price[i-1]]+pages[i-1]);
        }
    }

    cout << dp[n][x] << endl;
}