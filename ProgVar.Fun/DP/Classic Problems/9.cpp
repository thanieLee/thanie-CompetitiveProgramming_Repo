#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll MOD = 1000000007;
    ll n, x; cin >> n >> x;
    vector<ll> arr;
    for (int i = 0; i < n; i++) {
        ll xi; cin >> xi;
        arr.push_back(xi);
    }

    vector<ll> dp(1000001, 0);
    dp[0] = 1;
    for (int j = 0; j < n; j++) {
        for (int i = 1; i < x+1; i++) {
            if (arr[j] <= i) {
                dp[i] += dp[i-arr[j]];
                dp[i] %= MOD;
            }
        }
    }

    cout << dp[x]%MOD << endl;

}