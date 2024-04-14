#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
string s, x; 
ll n; 
vector<vector<ll>> dp;

ll solve(int i, ll md) {
    if (dp[i][md] != -1) {
        return dp[i][md];
    } else if (i == n-1) {
        ll m1 = (md*10)%7;
        ll m2  = ((md*10)%7+(s[i]-'0'))%7;
        if ((m1 == 0 or m2 == 0) and x[i] == 'T') {
            return 1;
        } else if ((m1 != 0 or m2 != 0) and x[i] == 'A') {
            return 1;
        }
        return 0;
    } else {
        ll c1 = solve(i+1, ((md*10)%7+(s[i]-'0'))%7);
        ll c2 = solve(i+1, (md*10)%7);
        char cur = x[i], next = x[i+1];
        if (cur == next) {
            if (c1 == 1 or c2 == 1) {
                return dp[i][md] = true;
            }
        } else {
            if (c1 == 0 or c2 == 0) {
                return dp[i][md] = true;
            }
        }
        return dp[i][md] = false;
    }

}

int main(){
    cin >> n;
    cin >> s >> x;
    dp.resize(n, vector<ll>(7, -1));
    ll win = solve(0, 0);
    if (win) {
        if (x[0] == 'A') {
            cout << "Aoki" << endl;
        } else {
            cout << "Takahashi" << endl;
        } 
    } else {
        if (x[0] == 'T') {
            cout << "Aoki" << endl;
        } else {
            cout << "Takahashi" << endl;
        } 
    }
}