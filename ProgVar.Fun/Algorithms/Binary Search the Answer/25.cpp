#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
ll n, k; 
vector<ll> arr, posArr, negArr;
bool cmp(ll M) {
    return true;
}

template <typename Can> ll bsearch(ll L, ll R, const Can& can) {
    while(R - L > 1) {
        ll M = L + (R-L) / 2;
        (can(M) ? L : R) = M;
    }
    return L;
}


int main(){
    cin >> n >> k;
    ll pos = 0, neg = 0;
    for (int i = 0; i < n; i++) {
        ll ai; cin >> ai;
        arr.push_back(ai);
        if (ai >= 0) {
            pos++;
            posArr.push_back(ai);
        }
        else {
            neg++;
            negArr.push_back(ai);
        }
    }
    sort(posArr.begin(), posArr.end());
    sort(negArr.begin(), negArr.end());
    if (k <= pos*neg) {
        ll p = (k-1)/neg;
        ll r = (k-1) % neg;
        cout << p << " " << r << endl;
        cout << posArr[p] * negArr[r] << endl;
    } else {
        vector<ll> check;
        vector<pll> points;

        int curNeg = 0;
        for (int i = 0; i < posArr.size(); i++) {
            
        }
    }
}