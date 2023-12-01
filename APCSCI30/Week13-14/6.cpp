#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef long long int ll;


ll b1 = 17;
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
        x = mod(x, p);
        x = (x*x);
        x = mod(x, p);
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

struct hashNode{
    deque<char> arr;
    ll startHash, endHash, wholeHash, startLim, endLim;

    hashNode(ll sLim, ll eLim){
        startHash = 0;
        endHash = 0;
        wholeHash = 0;
        arr = {};
        startLim = sLim;
        endLim = eLim; 
    }

    void addStart(char c){
        wholeHash = add(inv3, b3, m3, wholeHash, c, arr.size());
        if (arr.size() < startLim){
            startHash = add(inv1, b1, m1, startHash, c, arr.size());
        }
        endHash = add(inv2, b2, m2, endHash, c, arr.size());
        arr.push_back(c);
    }

    void rollEnd(char c){
        endHash = roll(inv2, b2, m2, endHash, c, arr[arr.size()-endLim], endLim);
    }

    void addChar(char c){
        wholeHash = add(inv3, b3, m3, wholeHash, c, arr.size());
        rollEnd(c);
        arr.push_back(c);
    }

    void removeBegin(){
        startHash = add(inv1, b1, m1, startHash, arr[startLim], startLim);
        startHash = mod(mod_mul(inv1, startHash - arr[0], m1), m1);
        wholeHash = mod(mod_mul(inv3, wholeHash - arr[0], m3), m3);
        arr.pop_front();
    }

    ll hashVal(){
        return mod((mod_mul(startHash, mod_pow(2, 32, m3), m3))+(mod(endHash, m3)), m3);
    }


};

int main(){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    cin.tie(0)->sync_with_stdio(0);
    string x, y, z; cin >> x >> y >> z;
    if (y.size() > x.size() or z.size() > x.size()){
        cout << 0 << endl;
        return 0;
    }
    unordered_map<ll, unordered_set<ll>> hashMap;
    ll yHash = 0;
    for (int i = 0; i < min(y.size(), z.size()); i++){
        yHash = add(inv1, b1, m1, yHash, y[i], i);
    }
    hashNode baseHash(y.size(), z.size());
    ll idx = 0;
    while (baseHash.arr.size() < z.size()){
        baseHash.addStart(x[idx]);
        idx++;
    }
    for (int i = 0; i < x.size()-z.size()+1; i++){
        if (i != 0){
            baseHash.addChar(x[i+z.size()-1]);
            baseHash.removeBegin();
        }
        hashNode newHash = baseHash;
        //cout << newHash.startHash << " " << yHash << endl;
        if (newHash.startHash != yHash) continue;
        //cout << "hehe" << endl;
        hashMap[newHash.hashVal()].insert(newHash.wholeHash);
        for (int j = i+idx; j < x.size(); j++){
            newHash.addChar(x[j]);
            hashMap[newHash.hashVal()].insert(newHash.wholeHash);
        }
    }

    string newString = y+z;
    
    hashNode testHash(y.size(), z.size());
    ll cnt = 0;
    while (testHash.arr.size() < z.size()){
        testHash.addStart(newString[cnt]);
        cnt++;
    }

    while (cnt < newString.size()){
        testHash.addChar(newString[cnt]);
        cnt++;
    }

    cout << hashMap[testHash.hashVal()].size() << endl;

    gettimeofday(&end, NULL);
 
 
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -start.tv_usec)) * 1e-6;
    //cout << fixed << time_taken << setprecision(10) << endl;
}