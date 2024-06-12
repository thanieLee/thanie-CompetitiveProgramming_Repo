#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main() {
    int n; cin >> n;
    vector<ll> dams;
    for (int i = 0; i < n; i++) {
        ll di; cin >> di;
        dams.push_back(di);
    }

    // for (ll i = 2; i <= 6; i+=2) {
    //     ll curMoun = i;
    //     for (int j = 1; j < n; j++) {
    //         curMoun = (dams[j-1]-(curMoun/2)) * 2;
    //     }
    //     //cout << (curMoun/2)+i/2 << " " << dams[n-1] << endl;
    // }

    ll l = 0, r = 2000000001;
    ll mid = (l+r)/2;
    ll tries = 0;
    if (dams[n-1] == 0 or dams[0] == 0) {
        l = 0; r = 0;
    } else {
        while (l < r and tries < 500) {
            //cout << l << " " << mid << " " << r << endl;
            mid = (l+r)/2;
            ll curMoun = mid;
            for (int j = 1; j < n; j++) {
                curMoun = (dams[j-1]-curMoun);
            }

            if ((curMoun + mid) == dams[n-1]) {
                l = mid;
                r = mid;
            } else if ((curMoun + mid) < dams[n-1]) {
                l = mid;
            } else {
                r = mid;
            }
            tries++;
            //cout << (curMoun+mid) << " " << dams[n-1] << endl;
        }
    }

    //cout << l << " " << r << endl;
    ll finalMoun;
    if (l+mid == dams[n-1])
        finalMoun = l*2;
    else
        finalMoun = r*2;
    vector<ll> ans(n);
    ans[0] = finalMoun;

    for (int i = 1; i < n; i++) {
        ans[i] = (dams[i-1]-ans[i-1]/2)*2;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}