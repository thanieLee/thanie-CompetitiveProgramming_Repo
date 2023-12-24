#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MOD 1000000007
vector<ll> fact;

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
 
ll mod_mul(ll a, ll b, ll m)
{
    ll res = 0;
    a = mod(a,m);
    while (b > 0)
    {
        if (b % 2 == 1)
            res = mod((res + a),m);
 
        a = mod((a * 2), m);
        b /= 2;
    }
 
    return mod(res, m);
}
ll comb(ll n, ll r){
    if (r > n or r < 0) return 0;
    return mod_div(fact[n], mod_mul(fact[n-r], fact[r], MOD), MOD);
}


int main(){
    ll n, m, k; cin >> n >> m >> k;
    fact.resize(2*pow(10, 6) + 1);
    fact[0] = 1;
    ll cur = 1;
    for (ll i = 1; i <= 2000000; i++){
        cur *= i;
        cur = mod(cur, MOD);
        fact[i] = cur;
    }
    
    if (m+k < n) {
        cout << 0 << endl;
        return 0;
    }

    ll tempAns = comb(n+m, n)-comb(n+m, n-k-1);
    //cout << comb(n+m, (int)ceil((n+m)/2)) << " " << comb(n+m, n-k-1) << endl;
    cout << mod(tempAns, MOD) << endl;
}