#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


ll no5(ll n) {
    ll ans = 0;
    while (n%5 == 0) ans++;
    return ans;
}

ll no2(ll n) {
    ll ans = 0;
    while (n%2 == 0) ans++;
    return ans;
}

int main(){
    ll n, k; cin >> n >> k;
    vector<ll> arr, arr2, arr5;
    for (int i = 0; i < n; i++) {
        ll ai; cin >> ai;
        arr.push_back(ai);
        arr2.push_back(no2(ai));
        arr5.push_back(no5(ai));
    }

    vector<vector<ll>> dp(202, vector<ll>(5201, 0));
    for (int i = 1; i <= n; i++) {
        for (int l = arr5[i-1]; l < 5199; l++) {
            dp[0][]
        }
        for (int j = 1; j <= k; j++) {
            for (int l = arr5[i-1]; l < 5199; l++) {
                dp[i][j][l] = max(dp[j][l], dp[i-1][j])
            }
        }
    }
}