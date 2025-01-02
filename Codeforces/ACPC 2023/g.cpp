#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
 
typedef tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
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
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<ll> a;
        ordered_multiset a_set;
        set<ll> mexs;
        for (int i = 0; i < n; i++) {
            ll x; cin >> x;
            a_set.insert({x, i});
        }

        if (a_set.find_by_order(0)->first != 0) {
            cout << 0 << endl;
            continue;
        } else {
            ll current = 0;
            ll perm = 1;
            ll ans = 0;
            while (a_set.lower_bound({current+1, -1})->first == current+1) {
                ll cnt = a_set.order_of_key({current+1, -1}) - a_set.order_of_key({current, -1});
                //cout << current << " " << cnt << endl;
                perm *= mod_pow(2, cnt, MOD)-1;
                perm = mod(perm, MOD);
                ll bigger = n - a_set.order_of_key({current+2, -1});
                current++;
                ans += (perm)*current*(mod_pow(2, bigger, MOD));
                ans = mod(ans, MOD);
            }
            //cout << ans << endl;
            current++;
            ll bigger = n - a_set.order_of_key({current+1, -1});
            ans += (perm)*(current)*(mod_pow(2, bigger, MOD));
            ans = mod(ans, MOD);
            cout << ans << endl;
        }
    }
}