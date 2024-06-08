#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<int> x;
    int total = 0;
    for (int i = 0; i < n ; i++) {
        int xi; cin >> xi;
        x.push_back(xi);
        total += xi;
    }

    int pos = 0, neg = 0;
    vector<int> pref(n+1, 0), suff(n+1, 0);
    pref[1] = abs(x[0]);
    if (x[0] > 0) {
        pos += x[0];
    } else {
        neg -= x[0];
    }
    for (int i = 1; i < n; i++) {
        if (x[i] > 0) {
            pos += x[i];
        } else {
            neg -= x[i];
        }

        pref[i+1] = max(pref[i]+x[i], neg-pos);
    }

    pos = 0; neg = 0;
    suff[n-1] = abs(x[n-1]);
    if (x[n-1] > 0) {
        pos += x[n-1];
    } else {
        neg -= x[n-1];
    }

    for (int i = n-1; i > 0; i--) {
        if (x[i] > 0) {
            pos += x[i-1];
        } else {
            neg -= x[i-1];
        }

        suff[i-1] = max(suff[i]+x[i-1], neg-pos);
    }

    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, pref[i]+suff[i]);
    }

    cout << ans << endl;


}