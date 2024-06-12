#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    ll l, r; cin >> l >> r;

    ll ans = 2020;
    for (ll i = l; i <= min(l+2020, r); i++) {
        for (ll j = i+1; j <= min(l+2020, r); j++) {
            ans = min(ans, (((i*j)%2019ll)+2019ll)%2019ll);
        }
    }
    cout << ans << endl;
}