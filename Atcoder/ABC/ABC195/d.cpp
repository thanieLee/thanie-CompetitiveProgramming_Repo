#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

bool cmp(pll &x, pll &y) {
    if (x.first == y.first) {
        return x.second < y.second;
    }
    return x.first < y.first;
}

int main(){
    ll n, m, q; cin >> n >> m >> q;
    vector<pll> bag;
    for (int i = 0; i < n; i++) {
        ll wi, vi; cin >> wi >> vi;
        bag.push_back({wi, vi});
    }
    sort(bag.begin(), bag.end(), cmp);

    vector<ll> boxes;
    for (int i = 0; i < m; i++) {
        ll xi; cin >> xi;
        boxes.push_back(xi);
    }

    for (int i = 0; i < q; i++) {
        ll l, r; cin >> l >> r; l--; r--;
        vector<bool> valid(m, true);
        for (int i = l; i <= r; i++) {
            valid[i] = false;
        }

        ll ans = 0;
        multiset<ll> box;
        for (int i = 0 ; i < m; i++) {
            if (valid[i]) box.insert(boxes[i]);
        }
        vector<bool> taken(n, false);
        for (auto it = box.begin(); it != box.end(); it++) {
            int curBag = -1;
            ll curVal = -1;
            for (int i = 0; i < n; i++) {
                if (!taken[i]) {
                    if (bag[i].first <= *it and bag[i].second > curVal) {
                        curBag = i;
                        curVal = bag[i].second;
                    }
                }
            }

            if (curBag != -1) {
                taken[curBag] = true;
                ans += curVal;
            }
        }
        cout << ans << endl;


    }
}