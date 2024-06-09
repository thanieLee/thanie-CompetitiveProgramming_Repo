#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll f(ll l, ll r, vector<ll> &x, ll s) {
    ll ans = 0;
    for (int i = l; i <= r; i++) {
        for (int j = i; j <= r; j++) {
            ll cur = 0;
            for (int k = i; k <= j; k++) {
                cur += x[k];
            }

            if (cur == s) {
                ans++;
            }
        }
    }
    return ans;
}


int main(){
    ll n, s; cin >> n >> s;
    vector<ll> a;
    for (int i = 0; i < n; i++) {
        ll ai; cin >> ai;
        a.push_back(ai);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            ans += f(i, j, a, s);
        }
    }

    cout << ans << endl; 
}
