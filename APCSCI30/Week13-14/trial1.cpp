#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int t; cin >> t;
    while (t--){
        ll n; cin >> n;
        vector<ll> arr(n);
        for (int i = 0; i < n; i++){
            ll x; cin >> x;
            arr[i] = x;
        }

        vector<ll> suff(n);
        suff[n-1] = arr[n-1];
        for (int i = n-1; i > 0; i--){
            suff[i-1] = suff[i]+arr[i-1];
        }
        ll ans = suff[0];
        for (int i = 1; i < n; i++){
            if (suff[i] > 0) {
                ans += suff[i];
            }
        }
        cout << ans << endl;
    }
}