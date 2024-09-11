#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int a, b, c; cin >> a >> b >> c;
    int ans = 0;
    while (a > 0) {
        ans += 2;
        a--;
    }

    if (c >= 2) {
        c -= 2;
        ans += 3;
        ans += 2*b;

    }

    while (c >= 2) {
        ans += 3;
        c -= 2;
    }
    cout << ans << endl;
}