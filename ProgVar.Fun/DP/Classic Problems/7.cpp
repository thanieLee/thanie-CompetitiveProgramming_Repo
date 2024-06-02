#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll n; cin >> n;
    vector<ll> arr;
    for (int i = 0; i < n; i++) {
        ll xi; cin >> xi;
        arr.push_back(xi);
    }

    vector<ll> dp(n+1, -10000000000);
    dp[0] = arr[0];
    ll ans = dp[0];
    for (int i = 1; i < n; i++) {
        dp[i] = max(arr[i], dp[i-1]+arr[i]);
        ans = max(dp[i], ans);
    }

    cout << ans << endl;
}