#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


ll solve(ll st, ll en, vector<ll> &freq, vector<ll> &cost, vector<vector<ll>> &dp) {
    if (en <= st) return 0;

    if (dp[st][en] != -1) return dp[st][en];
    ll mn = 1000000000000000;
    ll temp = freq[en+1] - freq[st];
    for (ll k = st; k <= en; k++) {
        mn = min(mn, solve(st, k-1, freq, cost, dp) + solve(k, k,freq,cost,dp) + solve(k+1, en, freq, cost, dp) + temp -cost[k]);
    }

    return dp[st][en] = mn;
}

int main(){
    ll n;
    while (cin >> n) {
        vector<ll> arr;
        for (ll i = 0; i < n; i++) {
            ll ai; cin >> ai;
            arr.push_back(ai);
        }

        vector<ll> freq;
        freq.push_back(0);
        ll cum = 0;
        for (ll i = 0; i < n; i++) {
            cum += arr[i];
            freq.push_back(cum);
        }

        vector<vector<ll>> dp(n+1, vector<ll>(n+1, -1));
        cout << solve(0, n-1, freq, arr, dp) << endl;

    }
}