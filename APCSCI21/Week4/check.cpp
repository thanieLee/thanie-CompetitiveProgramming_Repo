
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) x.size()
typedef pair<ll, ll> pll;

int main() {
    string s; cin >> s;
    ll ans = 0;
    for (int i = 0; i < len(s); i++) {
        for (int j = i+1; j < len(s); j++) {
            if (s[i] == 's' and s[j] == 'h') ans++;
        }
    }

    cout << ans << endl;
}