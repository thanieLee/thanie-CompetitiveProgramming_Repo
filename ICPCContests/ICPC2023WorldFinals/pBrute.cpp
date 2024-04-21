#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<ll> state;
vector<vector<ll>> lights;
ll ans = 100000000000;
ll l, b;

void solve(ll rCnt, ll gCnt, ll bCnt, ll press, ll idx) {
    if (rCnt == l) {
        ans = min(press, ans);
    }
    if (idx == l) {
        return;
    } else {
        solve(rCnt, gCnt, bCnt, press, idx+1);
        for (int i = 0; i < lights[idx].size(); i++) {
            ll cur = lights[idx][i];
            ll old = state[cur], ne = (state[cur]+1)%3;
            state[cur] = ne;
            if (old == 0) {
                rCnt--;
                gCnt++;
            } else if (old == 1) {
                gCnt--;
                bCnt++;
            } else {
                bCnt--;
                rCnt++;
            }
        }
        solve(rCnt, gCnt, bCnt, press+1, idx+1);
        for (int i = 0; i < lights[idx].size(); i++) {
            ll cur = lights[idx][i];
            ll old = state[cur], ne = (state[cur]+1)%3;
            state[cur] = ne;
            if (old == 0) {
                rCnt--;
                gCnt++;
            } else if (old == 1) {
                gCnt--;
                bCnt++;
            } else {
                bCnt--;
                rCnt++;
            }
        }
        solve(rCnt, gCnt, bCnt, press+2, idx+1);
        for (int i = 0; i < lights[idx].size(); i++) {
            ll cur = lights[idx][i];
            ll old = state[cur], ne = (state[cur]+1)%3;
            state[cur] = ne;
            if (old == 0) {
                rCnt--;
                gCnt++;
            } else if (old == 1) {
                gCnt--;
                bCnt++;
            } else {
                bCnt--;
                rCnt++;
            }
        }
    }
}
int main(){
    cin >> l >> b;
    string s;
    cin >> s;
    state.resize(s.size());
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
            state[i] = 0;
            r++;
        } else if (s[i] == 'G') {
            state[i] = 1;
            g++;
        } else {
            state[i] = 2;
            b++;
        }
    }

    solve(r, g, b, 0, 0);
    if (ans == 100000000000) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }
}