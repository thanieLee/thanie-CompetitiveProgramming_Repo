#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

bool cmp3(int S, int M, vector<pll> &arr, ll d) {
    if (arr[M].first-arr[S].first < d) return true;
    return false;
}


template <typename Can> int bsearch(int S, int L, int R, const Can& can, vector<pll> &arr, ll d) {
    while(R - L > 1) {
        int M = L + (R-L) / 2;
        (can(S, M, arr, d) ? L : R) = M;
    }

    return L;
}

bool cmp1(pll &x, pll &y) {
    if (x.first == y.first) return x.second < y.second;
    return x.first < y.first;
}

bool cmp2(pll &x, pll &y) {
    if (x.second == y.second) return x.first < y.first;
    return x.second < y.second;
}

int main(){
    ll n, d; cin >> n >> d;
    vector<pll> arr;
    for (int i = 0; i < n; i++) {
        ll mi, si; cin >> mi >> si;
        arr.push_back({mi, si});
    }

    sort(arr.begin(), arr.end(), cmp1);
    vector<ll> cum = {0};
    ll cnt = 0;

    for (int i = 0; i < n; i++) {
        cnt += arr[i].second;
        cum.push_back(cnt);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int nex = bsearch(i, i, n, cmp3, arr, d);
        ans = max(ans, cum[nex+1]-cum[i]);
    }

    cout << ans << endl;
}