#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) (int)(x.size())

ll mod(ll x, ll m){
    if (m == 0) return 0;
    if (m < 0) m *= -1;
    return (x%m + m)%m;
}

ll extended_euclid(ll a, ll b, ll &x, ll &y){
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
    ll g = extended_euclid(a, m ,x ,y);
    if (g == 1 || g == -1) return mod(x * g, m);

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

bool isPrime(ll x) {
    if (x == 2 or x == 3) return true;

    for (int i = 2; i < ceil(sqrt(x))+1; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

vector<pair<ll, ll>> findAllFactors(ll x, vector<ll> &primes, vector<bool> &prime){
    ll c = x;
    vector<pair<ll, ll>> fac;
    for (int i = 2; i < ceil(sqrt(x))+1;i++){
        if (!prime[i]) continue;
        int cnt = 0;
        while (c % i == 0) {
            cnt++;
            c/=i;
        }

        if (cnt > 0) fac.push_back({find(primes.begin(), primes.end(), i)-primes.begin(), cnt});
    }

    if (c != 1) {
        fac.push_back({find(primes.begin(), primes.end(), c)-primes.begin(), 1});
    }
    return fac;
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
    int n; cin >> n;
    vector<ll> arr;
    vector<ll> primes;
    vector<bool> prime(1000001, false);
    ll m = 1000000007;
    for (ll i = 2; i < 1000001; i++){
        if (isPrime(i)) {
            primes.push_back(i);
            prime[i] = true;

        }
    }

    for (int i = 0; i < n; i++){
        ll x; cin >> x;
        arr.push_back(x);
    }
    
    ll mul = 1;
    vector<ll> primeFactorization(primes.size(), 0);
    for (int i = 0; i < n; i++){
        vector<pair<ll, ll>> test = findAllFactors(arr[i], primes, prime);

        for (int j = 0; j < test.size(); j++) {
            primeFactorization[test[j].first] = max(primeFactorization[test[j].first], test[j].second);
            //cout << primes[test[j].first] << " " << test[j].second << endl;
        }
    }
    for (int i = 0; i < primes.size(); i++){
        mul = mod_mul(mod_pow(primes[i], primeFactorization[i], m), mul, m);
    
    }
    //cout << mul << endl;
    ll ans = 0;
    for (int i = 0; i < n; i++){
        ans += mod_div(mul, arr[i], m);
        ans = mod(ans, m);
    }
    cout << ans << endl;
}