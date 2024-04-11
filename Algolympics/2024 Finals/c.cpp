#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

int main(){
    ios_base::sync_with_stdio(false);
    int f; cin >> f;
    map<string, int> qual;
    for (int i = 0; i < f; i++) {
        string s; cin >> s;
        qual[s] = i;
    }

    vector<ll> dp(1<<(f), 0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        ll cur = 0;
        ll val; cin >> val;
        string s; cin >> s;
        while (s != "sry") {
            cin >> s;
            cur |= (1<<qual[s]);
            cin >> s;
        }
        dp[cur] = max(dp[cur], val);
    }

    for (int i = 1; i < 1<<(f); i++) {
        for (int j = 0; j < f; j++) {
            if (!(i & (1<<j))) {
                dp[i|(1<<j)] = max(dp[i|(1<<j)], dp[i]);
            }
        }
    }
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        ll cur = (1<<(f))-1;
        string s; cin >> s;
        while (s != "pls") {
            cin >> s;
            cur &= ~(1<<qual[s]);
            cin >> s;
        }

        ll ans = dp[cur];
        if (ans == 0) {
            cout << "LOWER YOUR STANDARDS" << '\n';
        } else {
            cout << ans << '\n';
        }
    }
}