#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

map<string, ll> ans;

void solve(ll cur, ll prev, bool is_start, string s) {
    if (cur > (ll)pow(2, 47)) return;
    if (cur == 1 or cur == 2 or cur == 4) return;
    if (!is_start) {
        if (ans.find(s) == ans.end()) {
            ans[s] = prev;
        } else {
            if (ans[s] > prev) {
                ans[s] = prev;
            } else {
                return;
            }
        }
    }

    if (is_start) {
        solve((cur-1)/3, cur, false, s);
    } else {
        if (cur%2 == 0) {
            if ((cur-1)%3 == 0) {
                solve((cur-1)/3, cur, false, s+'E');
            }
            solve(cur*2, cur, false, s+'E');
        } else {
            if ((cur-1)%3 == 0)
                solve((cur-1)/3, cur, false, s+'O');
            solve(cur*2, cur, false, s+'O');
        }
    }
}

int main(){
    string s; cin >> s;
    reverse(s.begin(), s.end());

    for (ll i = 8; i < (ll)pow(2, 47)+1; i*=2) {
        if ((i-1)%3 != 0) continue;
        ll cur = i;
        string cur_s;
        solve(i, -1, true, cur_s);
    }

    if (ans.find(s) == ans.end()){
        cout << "INVALID" << endl;
    } else {
        cout << ans[s] << endl;
    }
}