#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
pld reflectxa(ld x, ld y, ld a) {
    ld nextx = x-a;
    ld nexty = y;

    ld refx = -nextx;
    ld refy = nexty;

    return {refx+a, refy};
}

pld rot90(ld x, ld y, ld midx, ld midy) {
    ld nextx = x-midx;
    ld nexty = y-midy;

    ld rotx = nexty;
    ld roty = -nextx;

    return {rotx+midx, roty+midy};
}

ld solve(ld dep, ld x, ld y) {
    cout << dep << " " << x << " " << y << endl;
    if (dep < 1) return x*y;
    ld half = dep/2;
    if (x < half and y < half) {
        return solve(half, y, x);
    } else if (x < half and y >= half) {
        cout << "test2 " << (half*half) << endl;
        return (half*half) + solve(half, x, y-half);
    } else if (x >= half and y >= half) {
        cout << "test3 " << 2*(half*half) << endl;
        return 2*(half*half) + solve(half, x-half, y-half);
    } else {
        cout << "test4 " << 3*(half*half) << endl;
        ld newx = x-half;
        ld newy = y;
        pld rot = rot90(newx, newy, half/2, half/2);
        pld ref = reflectxa(rot.first, rot.second, half/2);

        return 3*(half*half) + solve(half, rot.first, rot.second);
    }
}

int main(){
    ll n, s; cin >> n >> s;
    vector<pair<pll, string>> words;

    for (int i = 0; i < n; i++) {
        ll x, y; string s; cin >> x >> y >> s;
        words.push_back({{x, y}, s});
    }

    cout << solve(5, 5, 0) << endl;

    pld next = rot90(4, 0, 2, 2);
    pld ans = reflectxa(next.first, next.second, 2);
    cout << ans.first << " " << ans.second << endl;
    cout << next.first << " " << next.second << endl;
}