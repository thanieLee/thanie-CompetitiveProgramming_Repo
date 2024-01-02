#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;



bool isPrime(ll n) {
    if (n==2||n==3){
        return true;
    }

    if (n <= 1 or n % 2 == 0 or n % 3 == 0){
        return false;
    }

    for (int i = 5; pow(i, 2) <= n; i += 6){
        if (n % i == 0 || n % (i + 2) == 0){
            return false;
        }
    }
    return true;
}

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

int main(){
    ll n; cin >> n;
    ll x, y;
    while (n--){
        ll a, b; cin >> a >> b;
        ll g = extended_euclid(a, b, x, y);
        bool didBreak = false;
        for (ll i = b; i >= 1; i--){
            if (isPrime(i)) {
                if (((b*i)/a <= a or ((b*i)/a) == b or ((b*i)/a) == (b * i)) and mod((b*i),a) == 0 and (b*i) <= 1000000000ll) {
                    cout << i * b << endl;
                    didBreak = true;
                    break;
                }
            }
        }
    }
}