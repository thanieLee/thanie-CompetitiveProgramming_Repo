#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<vector<ll>> lights;
ll ans = 100000000000;
ll l, b;

struct tupe {
    ll r, g, b;
    
    tupe (ll x, ll y, ll z) {
        r = x;
        g = y;
        b = z;
    }
};

tupe del(ll idx, ll shift) {
    ll ri=0, gi=0, bi=0;
    for ()
}


int main(){
    cin >> l >> b;
    string s;
    cin >> s;
    for (int i = 0; i < b; i++) {
        vector<ll> cur;
        ll cnt; cin >> cnt;
        for (int i = 0; i < cnt; i++) {
            ll x; cin >> x; x--;
            cur.push_back(x);
        }
        lights.push_back(cur);
    }
    ll r = 0, g = 0, b = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'R') {
            r++;
        } else if (s[i] == 'G') {
            g++;
        } else {
            b++;
        }
    }

    vector<vector<vector<vector<ll>>>> dp(l, vector<vector<vector<ll>>>(3, vector<vector<ll>>(3, vector<ll>(3, 1000000000))));

    dp[0][r][g][b] = 0;
    
}