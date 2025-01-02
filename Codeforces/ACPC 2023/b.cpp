#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
        vector<ll> a, b;
        ll a_gcd = -1, b_gcd = -1;
        for (int i = 0; i < n; i++) {
            ll x; cin >> x;
            a.push_back(x);
            if (i == 0) a_gcd = x;
            else
                a_gcd = gcd(x, a_gcd);
        }

        for (int i = 0; i < n; i++) {
            ll x; cin >> x;
            b.push_back(x);

            if (i == 0) b_gcd = x;
            else
                b_gcd = gcd(x, b_gcd);
        }

        int ans = 0;
        if (a_gcd%b_gcd != 0) {
            ans++;
        }
        if (b_gcd%a_gcd != 0) {
            ans++;
        } 

        cout << ans << endl;
    }
}