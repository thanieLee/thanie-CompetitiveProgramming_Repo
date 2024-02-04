#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll n, k; cin >> n >> k;
    vector<ll> a;

    for (int i = 0; i < n; i++){
        ll ai; cin >> ai;
        a.push_back(ai);
    }
    ll ans = 0;

    for (int i = 0; i < n; i++){
        double cnt = 0;
        int temp = 0;
        for (int j = i; j < n; j++){
            cnt += a[j];
            if (cnt/(j-i+1) >= k) {
                temp++;
            }
        }
        ans += temp;
        cout << i << " " << temp << endl;
    }

    cout << ans << endl;
}