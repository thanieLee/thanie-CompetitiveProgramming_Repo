#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll solve(ll h) {
    if (h == 1) return 1;

    return 1 + 2*(solve(h/2));
}


int main(){
    ll h; cin >> h;
    cout << solve(h) << endl;
}