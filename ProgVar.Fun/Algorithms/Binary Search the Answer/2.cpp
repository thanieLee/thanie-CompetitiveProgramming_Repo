#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
ll d;
ll b = 0, s = 0, c = 0;
ll bHave, sHave, cHave;
ll bCost, sCost, cCost; 

bool cmp(ll M) {
    ll bTotal = b*M, sTotal = s*M, cTotal = c*M;
    ll cost = 0;
    cost += max(0ll, (bTotal-bHave))*bCost;
    cost += max(0ll, (sTotal-sHave))*sCost;
    cost += max(0ll, (cTotal-cHave))*cCost;

    return cost <= d;
}

template <typename Can> ll bsearch(ll L, ll R, const Can& can) {
    while(R - L > 1) {
        ll M = L + (R-L) / 2;
        (can(M) ? L : R) = M;
    }
    return L;
}

int main(){
    string borgir; cin >> borgir;
    cin >> bHave >> sHave >> cHave;
    cin >> bCost >> sCost >> cCost;
    cin >> d;
    for (int i = 0; i < borgir.size(); i++) {
        if (borgir[i] == 'B') b++;
        else if (borgir[i] == 'S') s++;
        else c++;
    }

    ll L = 0, R = 100000000000000;
    cout << bsearch(L, R, cmp) << endl;
}