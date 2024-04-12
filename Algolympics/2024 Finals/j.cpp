#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

bool cmp(pll &x, pll &y) {
    return (x.first*y.second) > (y.first*x.second);
}

int main(){
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<pll> hole(n);
        vector<ll> v ,t;
        for (int i = 0; i < n; i++) {
            ll vi; cin >> vi;
            v.push_back(vi);
        }
        
        for (int i = 0; i < n; i++) {
            ll ti; cin >> ti;
            t.push_back(ti);
        }

        for (int i = 0; i < n; i++) {
            hole[i] = {v[i], t[i]};
        }

        sort(hole.begin(), hole.end(), cmp);
        ll cnt = 0;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            cnt += hole[i].second;
            ans += cnt*hole[i].first;
        }
        cout << ans << endl;
    }
}