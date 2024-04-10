#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll MOD = 998244353;

ll solve(ll pos, ll msk, ll dec, ll &cur, ll hasVal, vector<vector<vector<vector<ll>>>> &dp, ll &k) {
    if (pos == -1){
        return 0;
    } else if (dp[pos][msk][dec][hasVal] != -1){
        return dp[pos][msk][dec][hasVal];
    } else {
        ll res = 0;
        ll limit;
        if (dec == 0) {
            limit = (to_string(cur)[pos]) - '0' + 2;

        } else {
            limit = 10;
        }

        cout << limit << " " << pos << " " << (to_string(cur)[pos]) << endl;

        for (int i = 0; i < limit; i++) {
            ll newDec = dec;

            ll newMsk = msk;
            ll newHas;
            newMsk |= (1<<i);

            if (__popcount(newMsk) > k) {
                continue;
            }

            if (dec == 0 and i < limit-1) {
                newDec = 1;
            }

            if (hasVal == 0 and i == 0) {
                newHas = 0;
            } else {
                newHas = 1;
            }

            res += solve(pos-1, i, newDec, cur, newHas, dp, k)+(pow(10, pos)*i);
        }

        return dp[pos][msk][dec][hasVal] = res;
    }
}

int main(){
    ll l, r, k; cin  >> l >> r >> k;
    vector dp((to_string(r).size()+1), vector((1<<11), vector(2, vector<ll>(2, -1))));
    ll ans = 0;
    ll cur = 9;
    ll temp = 1;

    for (ll i = l; i <= r; i++){
        set<char> digits;
        for (char c : to_string(i)) {
            digits.insert(c);
        }

        if (digits.size() <= k) {
            ans += i;
            ans %= MOD;
        }
    }

    cout << ans << endl;
    cout << solve(2, 0, 0, r, 0, dp, k) << endl;
    

}