#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
set<ll> pos;
vector<bool> prime(1000001, true);
vector<ll> primes;



void prime_sieve() {
    for (ll i = 2; i <= 1000000; i++) {
        if (prime[i]) {
            for (ll j = i+i; j <= 1000000; j+=i) {
                prime[j] = false;
            }
        }
    }
}


int main(){
    ll n; cin >> n;
    prime[0] = false;
    prime[1] = false;

    prime_sieve();

    set<pll> prime_factorials;
    for (int i = 2; i < 1000001; i++) {
        if (prime[i]) primes.push_back(i);
    }
    prime_factorials.insert({2, 1});
    ll cur = 2;
    ll idx = 1;
    ll cur_ans =  1;
    while (cur <= 1000000000000000000) {
        cur *= (ll)primes[idx];

        idx++;
        auto prev = prime_factorials.rbegin();
        ll prev_diff = prev->first-prev->second;
        ll jump = cur - prev->first;
        ll factor = jump/prev->first;
        if (cur > 0 and cur <= 1000000000000000000){
            prime_factorials.insert({cur, cur-prev_diff*factor});
        }
    }

    auto ans = prime_factorials.lower_bound({n, -1});
    if (ans->first != n) ans--;
    ll d = gcd(ans->first, ans->second);

    cout << ans->second/d << "/" << ans->first/d << endl;
}