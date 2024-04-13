#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
string s, x; 
ll n; 
vector<vector<ll>> dp;
vector<ll> pow10Mod7;

ll solve(int i, ll md) {
    if (dp[i][md] != -1) {
        return dp[i][md];
    }
    if (i == n-1) {
        ll c1 = (md+((s[i]-'0')*pow10Mod7[n-i-1])%7)%7;
        ll c2 = md;
        if (x[i] == 'T') {
            if (c1 == 0 or c2 == 0) {
                return dp[i][md] = 1;
            }
            return dp[i][md] = 0;

        } else {
            if (c1 == 0 and c2 == 0) {
                return dp[i][md] = 0;
            }
            return dp[i][md] = 1;
        }
    } else {
        char cur = x[i], next = x[i+1];
        if (cur != next) {
            ll c1 = solve(i+1, (md+((s[i]-'0')*pow10Mod7[n-i-1])%7)%7);
            ll c2 = solve(i+1, md);
            if (c1 == 0 or c2 == 0) {
                return dp[i][md] = 1;
            }
            return dp[i][md] = 0;
        } else {
            ll c1 = solve(i+1,(md+((s[i]-'0')*pow10Mod7[n-i-1])%7)%7);
            ll c2 = solve(i+1, md);
            if (c1 == 1 or c2 == 1) {
                return dp[i][md] = 1;
            }
            return dp[i][md] = 0;
        }
    }
}

int main(){
    cin >> n;
    cin >> s >> x;
    ll cur = 1;
    for (int i = 0; i <= 20000; i++) {
        cur %= 7;
        pow10Mod7.push_back(cur);
        cur *= 10;
    }
    dp.resize(n, vector<ll>(7, -1));
    bool win = solve(0, 0);

    if (win == 1) {
        if (x[0] == 'T')
            cout << "Takahashi" << endl;
        else
            cout << "Aoki" << endl;
    } else {
        if (x[0] == 'T')
            cout << "Aoki" << endl;
        else
            cout << "Takahashi" << endl;
    }
}