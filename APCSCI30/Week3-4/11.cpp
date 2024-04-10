#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll MOD = 998244353;
ll mod(ll x, ll m) {
	if (m == 0)
		return 0;
	if (m < 0)
		m *= -1;
	return (x % m + m) % m;
}

ll extended_euclid(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll g = extended_euclid(b, mod(a, b), x, y);
	ll z = x - a/b*y;
	x = y;
	y = z;
	return g;
}

ll mod_inv(ll a, ll m) {
	ll x, y;
	ll g = extended_euclid(a, m, x, y);
	if (g == 1 || g == -1)
		return mod(x * g, m);
	return 0;
}

ll mod_div(ll a, ll b, ll m) {
	a = mod(a, m);
	ll inv = mod_inv(b, m);
	return mod(inv * a, m);
}

ll mod_pow(ll x, ll y, ll p) 
{ 
    ll res = 1;
    x = mod(x,p);
    if (x == 0) return 0;
    while (y > 0) 
    { 
        if (y & 1) 
            res = mod(res*x, p);
        y = y >> 1;
        x = mod(x*x, p);
        res = mod(res, p);
    } 
    return res; 
} 

pair<ll, ll> solve(ll pos, ll msk, ll dec, ll &cur, ll hasVal, vector<vector<vector<vector<pair<ll, ll>>>>> &dp, ll &k) {
    if (cur == 0) return {0, 1};

    if (pos == -1){
        return {0, 1};
    } else if (dp[pos][msk][dec][hasVal].first != -1){
        //cout << pos << " " << msk << " " << dec << " " << hasVal << " " << cur << endl;
        return dp[pos][msk][dec][hasVal];
    } else {
        pair<ll, ll> res = {0, 0};
        ll limit;
        if (dec == 0) {
            limit = (to_string(cur)[to_string(cur).size()-pos-1]) - '0' + 1;

        } else {
            limit = 10;
        }

        //cout << limit << " " << pos << " " << cur << " yeep" << endl;

        for (int i = 0; i < limit; i++) {
            ll newDec = dec;
            ll newMsk = msk;
            ll newHas;


            if (dec == 0 and i < limit-1) {
                newDec = 1;
            }

            if (hasVal == 0 and i == 0) {
                newHas = 0;
            } else {
                newHas = 1;
            }  

            if (newHas == 1)
                newMsk |= (1<<i);
            pair<ll, ll> val = solve(pos-1, newMsk, newDec, cur, newHas, dp, k);
            //cout << bitset<11>(newMsk) << endl;
            if (__popcount(newMsk) <= k) {
            //cout << i << " " << pos-1 << " " << newHas << " " << newDec << " " << val.first << " " << (pow(10, pos)*i) << endl;
                res.first += val.first+(mod(mod(mod_pow(10, pos, MOD)*i, MOD)*val.second, MOD));
                res.first %= MOD;
                res.second += val.second;
                res.second %= MOD;
            }
        }
        return dp[pos][msk][dec][hasVal] = res;
    }
}

int main(){
    ll l, r, k; cin  >> l >> r >> k; l--;
    vector dp((to_string(r).size()+1), vector((1<<11), vector(2, vector<pair<ll, ll>>(2, {-1, -1}))));
    ll ans1 = 0;
    ll ans2 = solve(to_string(r).size()-1, 0, 0, r, 0, dp, k).first;
    dp.clear();
    dp.resize((to_string(l).size()+1), vector((1<<11), vector(2, vector<pair<ll, ll>>(2, {-1, -1}))));
    ll ans3 = solve(to_string(l).size()-1, 0, 0, l, 0, dp, k).first;
    cout << mod(ans2-ans3, MOD) << endl;
}