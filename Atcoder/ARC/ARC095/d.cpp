#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll n; cin >> n;
    vector<ll> x;
    for (int i = 0; i < n; i++) {
        ll xi; cin >> xi;
        x.push_back(xi);
    }

    sort(x.begin(), x.end());
    ll big = x[n-1];
    auto mid = upper_bound(x.begin(), x.end(), big/2);
    ll ans = 0;
    if (mid+1 != x.end()) {
        ans = max(ans, *mid);
    }
    //cout << ans << endl;
    mid--;
    if (n%2 == 0) {
        if (min(abs(big/2 - *mid), abs(*mid - (big/2+1))) <= min(abs(big/2 - ans), abs(ans - (big/2+1))) ) {
            ans = *mid;
        }   
    } else {
        //cout << abs(big/2+1 - *mid) << " " << abs(big/2+1 - ans) << endl;
        if (abs(big/2+1 - *mid) <= abs(big/2+1 - ans)) {
            ans = *mid;
        }
    }
    cout << big << " " << ans << endl;

}