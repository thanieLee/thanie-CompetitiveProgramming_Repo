#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) (int)(x.size())

int main(){
    ll x; cin >> x;
    ll ans = (x/11)*2;
    ll remain = x%11;
    if (remain > 0){
        if (remain > 6) {
            ans += 2;
        } else {
            ans += 1;
        }
    }
    cout << ans << endl;
}