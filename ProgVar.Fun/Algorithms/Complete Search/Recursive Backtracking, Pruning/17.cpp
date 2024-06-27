#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

 int main() {
    int n, m; cin >> n >> m;
    vector<ll> masks;
    vector<int> same;
    for (int i = 0; i < m; i++) {
        string a; cin >> a;
        int sme; cin >> sme;
        masks.push_back(stoll(a, nullptr, 2));
        same.push_back(sme);
    }
    ll ans = 0;
    for (ll msk = 0; msk < (1ll<<n); msk++) {
        bool can = true;
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if ((msk & (1ll<<j)) == (masks[i] & (1ll<<j))) cnt++;
            }
            if (cnt != same[i]) can = false;
        }

        if (can) {
            ans++;
            cout << bitset<6>(msk) << endl;
        }
    }

    cout << ans << endl;
}