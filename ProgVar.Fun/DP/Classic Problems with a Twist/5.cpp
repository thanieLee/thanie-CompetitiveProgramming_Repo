#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

int main(){
    ll n, k; cin >> n >> k;
    vector<ll> x;
    for (int i = 0; i < n; i++) {
        ll xi; cin >> xi;
        x.push_back(xi);
    }

    vector<ll> cnt = {0};
    ll cum = 0;
    for (int i = 0; i < n; i++) {
        cum += x[i];
        cnt.push_back(cum);
    }

    vector<pll> dp1(n+1, {0, -1});
    dp1[0] = {cnt[k], 0};
    for (int i = 1; i <= n-k; i++) {
        if (cnt[i+k]-cnt[i] > dp1[i-1].first) {
            dp1[i] = {cnt[i+k]-cnt[i], i};
        } else {
            dp1[i] = dp1[i-1];
        }
    }

    vector<pll> dp2(n+1, {0, -1});
    dp2[k] = {dp1[0].first + cnt[2*k]-cnt[k], k};
    for (int i = k+1; i <= n-k; i++) {
        //cout << dp1[i-k].first << " " << dp1[i-k].second << endl;
        if (dp1[i-k].first+cnt[i+k]-cnt[i] > dp2[i-1].first) {
            dp2[i] = {dp1[i-k].first+cnt[i+k]-cnt[i], i};
        } else {
            dp2[i] = dp2[i-1];
        }
    }
    //cout << endl;
    for (int i = 0; i <= n; i++) {
        //cout << dp1[i].first << " " << dp1[i].second << endl;
    }
    //cout << endl;
    for (int i = 0; i <= n; i++) {
        //cout << dp2[i].first  << " " << dp2[i].second << endl;
    }

    pll ans1 = dp2[n-k];



    cout << dp1[ans1.second-k].second+1 << " " << ans1.second+1 << endl;
}