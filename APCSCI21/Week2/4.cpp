#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
vector<ll> arr;

bool cmp(ll u, ll v) {
    if (arr[u] == arr[v]) {
        return u < v;
    }
    return arr[u] < arr[v];
} 

int main(){
    cerr.tie(NULL);
    ll n; cin >> n;
    for (ll i = 0; i < 1<<n; i++){
        ll x; cin >> x;
        arr.push_back(x);
    }

    vector<set<pll>> dp(1<<n+1);
    vector<int> ans(1<<n+1);
    dp[0].insert({arr[0], 0});
    for (int i = 1; i < 1<<n; i++) {
        dp[i].insert({arr[i], i});
        for (int j = 0; j < n; j++) {
            if ((i & (1<<j)) == 0) continue;
            for (auto v : dp[i & ~(1<<j)]) {
                dp[i].insert(v);
            }
            
            while (dp[i].size() > 2) {
                dp[i].erase(dp[i].begin());
            }
        }
    
        int cnt = 0;
        for (auto c : dp[i]) {
            cnt += c.first;
            cerr << c.first << " " << c.second << " | ";
        }
        //cout << endl;
        ans[i] = max(cnt, ans[i-1]);
        cout << ans[i] << endl;
    }
}