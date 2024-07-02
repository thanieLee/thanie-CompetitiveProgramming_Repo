#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;


int main(){
    int n, m; cin >> n >> m;
    vector<vector<pii>> mx(n+1);

    for (int i = 0; i < m; i++) {
        int xi, yi, zi; cin >> xi >> yi >> zi;
        mx[xi].push_back({yi, zi});
    }

    // for (int i = n-1; i >= 0; i--) {
    //     //mx[i] = min(mx[i], {mx[i+1].first-1, mx[i+1].second});
    //     cout << mx[i].first << " " << mx[i].second << endl;
    // }
    // cout << endl;
    vector<ll> dp(1<<n, 0);

    for (int msk = 1; msk < (1<<n); msk++) {
        int cnt = 0;
        vector<int> num(n+1, 0);
        for (int i = 0; i < n; i++) {
            if (msk & (1<<i)) cnt++;
            num[i+1] = cnt;
        }
        int len = __builtin_popcount(msk);
        if (len == 1) {
            int msb = -1;
            for (int i = 0; i < n; i++) {
                if (msk & (1<<i)) msb = i;
            }
            bool can = true;

            for (pii cond : mx[len]) {
                if (num[cond.first] > cond.second) can = false;
            }
            if (can) dp[msk] = 1;
        } else {
            bool can = true;

            for (pii cond : mx[len]) {
                if (num[cond.first] > cond.second) can = false;
            }

            if (!can) continue;
            for (int i = 0; i < n; i++) {
                if (!(msk & (1<<i))) continue;
                int prev = msk & ~(1<<i);

                dp[msk] += dp[prev];
            }
        }

    }

    cout << dp[(1<<n)-1] << endl;
}