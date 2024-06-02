#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll t; cin >> t;
    ll diff = 50000;
    while (t--) {
        vector<bool> dp(200004, false);
        ll n; cin >> n;
        if (n == 0) {
            cout << 0 << endl;
            continue;
        }
        vector<ll> arr;
        for (int i = 0; i < n; i++) {
            ll xi; cin >> xi;
            arr.push_back(xi);
        }

        dp[diff+arr[0]] = true;
        dp[diff-arr[0]] = true;
        for (int i = 1; i < n; i++) {
            vector<bool> p(200004, false);

            for (int j = 0; j < 100001; j++) {
                if (dp[j]) {
                    p[j-arr[i]] = true;
                    p[j+arr[i]] = true;
                }
            }

            dp = p;
        }
        ll ans = 1000000;
        for (int i = 0; i < 50001; i++) {
            if (dp[diff+i] or dp[diff-i]) ans = min((ll)i, ans);
        }

        cout << ans << endl;
    }
    return 0;
}