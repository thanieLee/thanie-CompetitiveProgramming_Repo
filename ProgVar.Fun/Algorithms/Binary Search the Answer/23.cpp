#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll a, b, x;
ll f(ll n) {
    ll cnt = to_string(n).size();
    return a * n + b * cnt;
}


bool cmp(ll M) {
    return f(M)<= x;
}

template <typename Can> ll bsearch(ll L, ll R, const Can& can) {
    while(R - L > 1) {
        ll M = L + (R-L) / 2;
        (can(M) ? L : R) = M;
    }
    return L;
}


int main(){
    cin >> a >> b >> x;
    ll L = 0, R = 1000000001;
    cout << bsearch(L, R, cmp) << endl;
}