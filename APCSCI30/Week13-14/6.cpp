#include <bits/stdc++.h>
#include <sys/time.h>
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

vector<int> zAlgo(string str, string pattern) {
    string s = pattern + "#" + str;
    int n = s.size();
    vector<int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0,min(z[i-x],y-i+1));
        while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
            x = i; y = i+z[i]; z[i]++;
        }
    }
    reverse(z.begin(), z.end());
    for (int i = 0; i < pattern.size()+1; i++){
        z.pop_back();
    }
    reverse(z.begin(), z.end());
    return z;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    string x, y, z; cin >> x >> y >> z;
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < x.size()+1; i++){
        bModPow.push_back(mod_pow(b1, i, m1));

        for (char c : alpha){
            modMul[c][i] = mod_mul(c, bModPow[i], m1);
        }
    }

    vector<int> pref = zAlgo(x, y);
    vector<int> suff = zAlgo(x, z);
    vector<unordered_set<ll>> hashMap(2001, unordered_set<ll>());
    vector<hashNode> hashes = {hashNode(0)};
    hashes[0].addHash(x[0]);
    if (y.size() == 1 and z.size() == 1 and y[0] == z[0]){
        for (int i = 0; i < x.size(); i++){
            if (x[i] == y[0]) {
                hashNode testNode(-1);
                testNode.addHash(x[0]);
                hashMap[1].insert(testNode.hashVal);
                break;
            }
        }
    }
    for (int i = 1; i < x.size(); i++){
        char cur = x[i];
        for (int j = 0; j < hashes.size(); j++){
            hashNode curHash = hashes[j];
            curHash.addHash(cur);
            hashes[j] = curHash;
            //cout << curHash.startingChar << " " << curHash.startingChar+curHash.hashLen-z.size() << endl;
            if (pref[curHash.startingChar]==y.size() and suff[curHash.startingChar+curHash.hashLen-z.size()]==z.size() and curHash.hashLen >= max(y.size(), z.size())){
                hashMap[curHash.hashLen].insert(curHash.hashVal);
            }
        }
        hashNode nextHash = hashNode(i);
        nextHash.addHash(cur);
        hashes.push_back(nextHash);
    }

    ll cnt = 0;
    for (int i = 0; i < x.size()+1; i++){
        //cout << i << " " << hashMap[i].size() << endl;
        cnt += hashMap[i].size();
    }
    cout << cnt << endl;

}