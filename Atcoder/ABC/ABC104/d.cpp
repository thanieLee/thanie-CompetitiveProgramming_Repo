#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int MOD = 1000000007;

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

int main(){
    string s; cin >> s;
    int validA = 0, validB = 0, validC = 0;
    int run = 1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'A') {
            validA += run;
            validA = mod(validA, MOD);
        } else if (s[i] == 'B') {
            validB += validA;
            validB = mod(validB, MOD);
        } else if (s[i] == 'C') {
            validC += validB;
            validC = mod(validC, MOD);
        } else {
            validC = mod_mul(validC, 3, MOD);
            validC += validB;
            validC = mod(validC, MOD);
            validB = mod_mul(validB, 3, MOD);
            validB += validA;
            validB = mod(validB, MOD);
            validA = mod_mul(validA, 3, MOD);
            validA += run;
            validA = mod(validA, MOD);
            run = mod_mul(run, 3, MOD);

        }
    }
    
    cout << validC << endl;
}