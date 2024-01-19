#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll x, y; cin >> x >> y;
    ll n, m;
    n = min(x, y);
    m = max(x, y);
    if (n == 1 and m == 1) {
        cout << 1 << endl;
    } else if (n == 1){
        cout << max(0ll, m-2) << endl;;
    } else if (n == 2) {
        cout << 0 << endl;
    } else {
        cout << (n-2) * (m-2) << endl;
    }

}