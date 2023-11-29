#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

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

int mod_pow(ll x, unsigned int y, ll p) 
{ 
    ll res = 1;
    x = mod(x,p);
    if (x == 0) return 0;
    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x);
            res = mod(res, p);
        y = y>>1;
        x = (x*x);
        res = mod(res, p);
    } 
    return res; 
}

ll h(ll b, ll m, string s){
    ll ans = 0;
    for (int i = 0; i < s.size(); i++){
        ans += mod_mul(s[i],mod_pow(b,i, m), m);
        ans = mod(ans, m);
    }
    return ans;
}

ll roll(ll inv, ll b, ll m, ll hash, char c, char r, ll size){
    hash = mod_mul(inv, hash-r, m);
    hash = mod(hash, m);
    hash += mod_mul(c, mod_pow(b, size-1, m), m);
    hash = mod(hash, m);
    return hash;
}

ll add(ll inv, ll b, ll m, ll hash, char c, ll size){
    hash += mod_mul(c, mod_pow(b, size, m), m);
    hash = mod(hash, m);
    return hash;
}

ll combine(ll hash1, ll hash2, ll m){
    return mod(mod_mul(hash1, mod_pow(2, 32, m), m) + mod(hash2, m), m);
}
int main(){
    string x, y, z; cin >> x >> y >> z;
    unordered_map<ll, set<ll>> hashMap;
    ll b1 = 17, b2 = 19, b3 = 11;
    ll m1 = 1000000007, m2 = 1000000009, m3 = 1000000033;
    ll inv1 = mod_inv(b1, m1), inv2 = mod_inv(b2, m2), inv3 = mod_inv(b3, m3);

    string main = "";
    for (int i = 0; i < max(y.size(), z.size()); i++){
        main += x[i];
    }
    string temp1 = "", temp2 = "";

    for (int i = 0; i < y.size(); i++){
        temp1 += x[i];
    }

    for (int i = main.size()-z.size(); i < main.size(); i++){
        temp2 += main[i];
    }

    cout << main << " " << temp1 << " " << temp2 << endl;
}