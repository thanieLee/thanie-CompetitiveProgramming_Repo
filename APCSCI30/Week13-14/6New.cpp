#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll b1 = 1000003;
ll b2 = 19;
ll b3 = 11;
ll m1 = 1000000007;
ll m2 = 1000000009;
ll m3 = 1000000033;
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
 
ll inv1 = mod_inv(b1, m1);
ll inv2 = mod_inv(b2, m2);
ll inv3 = mod_inv(b3, m3);
 
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
 
ll mod_pow(ll x, unsigned int y, ll p) 
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
        x = mod(x, p);
        x = (x*x);
        x = mod(x, p);
        res = mod(res, p);
    } 
    return res; 
}
 
vector<ll> bModPow;
map<char, map<ll, ll>> modMul;
ll add(ll inv, ll b, ll m, ll hash, char c, ll size){
    hash += modMul[c][size];
    hash = mod(hash, m);
    return hash;
}
 
struct hashNode{
    ll hashLen, hashVal, startingChar;
    hashNode(ll startingIdx){
        hashLen = 0;
        hashVal = 0;
        startingChar = startingIdx;
    }
 
    void addHash(char c){
        hashVal = add(inv1, b1, m1, hashVal, c, hashLen);
        hashLen++;
    }
};
int main(){
    string s, pref, suff;
    cin >> s >> pref >> suff;

    string alpha = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < s.size()+1; i++){
        bModPow.push_back(mod_pow(b1, i, m1));

        for (char c : alpha){
            modMul[c][i] = mod_mul(c, bModPow[i], m1);
        }
    }


    if (pref.length() > s.length() or suff.length() > s.length()){
        cout << 0 << endl;
        return 0;
    }
    vector<bool> prefPos(2001, false), suffPos(2001, false);
    for (int i = 0; i < s.length() - pref.length() + 1; i++){
        bool can = true;
        for (int j = 0; j < pref.length(); j++){
            if (s[i+j] != pref[j]) can = false;
        }

        prefPos[i] = can;
    }

     for (int i = 0; i < s.length() - suff.length() + 1; i++){
        bool can = true;
        for (int j = 0; j < suff.length(); j++){
            if (s[i+j] != suff[j]) can = false;
        }

        suffPos[i+suff.length()-1] = can;
    }

    vector<set<ll>> hashSet(2002, set<ll>());

    for (int i = 0; i < s.size(); i++){
        hashNode cur = hashNode(i);
        for (int j = i; j < s.size(); j++) {
            cur.addHash(s[j]);
            if (prefPos[i] and suffPos[j] and (j-i+1 >= max(pref.length(), suff.length()))) {

                hashSet[j-i+1].insert(cur.hashVal);
            }
        }
    }

    ll ans = 0;

    for (int i = 0; i <= 2001; i++){
        ans += hashSet[i].size();
    }

    cout << ans << endl;
}