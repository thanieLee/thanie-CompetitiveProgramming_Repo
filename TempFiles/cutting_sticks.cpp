#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


int solve(int st, int en, vector<int> &arr, vector<vector<int>> &dp) {
    if (st == en-1) {
        return 0;
    } else {
        if (dp[st][en] != -1) return dp[st][en];

        int mn = 50000000;
        for (int k = st+1; k < en; k++) {
            mn = min(mn, solve(st, k, arr, dp)+solve(k, en, arr, dp));
        }

        return dp[st][en] = mn + arr[en] - arr[st];
    }
}


int main(){
    int l; cin >> l;
    while (l != 0) {
        int n; cin >> n;
        vector<int> arr;
        arr.push_back(0);
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            arr.push_back(ai);
        }
        arr.push_back(l);

        vector<vector<int>> dp(n+3, vector<int>(n+3, -1));

        cout << "The minimum cutting is " << solve(0, n+1, arr, dp) << '.' << endl;

        cin >> l;
    }
}