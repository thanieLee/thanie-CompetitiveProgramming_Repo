#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll MOD = 1000000007;

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

int main(){
    ll n; cin >> n;
    vector<ll> a;
    for (int i = 0; i < n; i++) {
        ll ai; cin >> ai;
        a.push_back(ai);
    }

    vector<int> cnt_off(62, 0), cnt_on(62, 0);

    for (int i = 1; i < n; i++) {
        for (ll j = 0; j <= 61; j++) {
            if (a[i] & (1ll<<j)) {
                cnt_on[j]++;
            } else {
                cnt_off[j]++;
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < n-1; i++) {
        ll cur = a[i];
        for (ll j = 0; j <= 61; j++) {
            if (cur & (1ll<<j)) {
                ans += cnt_off[j]*mod_pow(2, j, MOD);
                ans = mod(ans, MOD);
            } else {
                ans += cnt_on[j]*mod_pow(2, j, MOD);
                ans = mod(ans, MOD);
            }
        }

        ll next = a[i+1];
        for (ll j = 0; j <= 61; j++) {
            if (next & (1ll<<j)) {
                cnt_on[j]--;
            } else {
                cnt_off[j]--;
            }
        }

    }

    cout << ans << endl;
}