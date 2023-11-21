#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll solve(string &a, string &b, ll &size, ll pos, ll prev, ll dec, ll hasVal, ll inc, vector<vector<vector<vector<vector<ll>>>>> &dp){
    if (pos == size){
        return dp[pos][prev][dec][hasVal][inc] = 1;
    } else {
        
        if (dp[pos][prev][dec][hasVal][inc] != -1){
            return dp[pos][prev][dec][hasVal][inc];
        }
        ll res = 1;
        ll ans = 0;
        ll limit;
        ll start;

        if (dec){
            limit = 9;
        } else {
            limit = b[pos]-'0';
        }

        if (inc){
            start = 0;
        } else {
            start = a[pos]-'0';
        }
        for (int i = start; i <= limit; i++){
            ll newDec = dec;

            if (i < b[pos]-'0'){
                newDec = 1;
            }

            ll newInc = inc;

            if (i > a[pos]-'0'){
                newInc = 1;
            }
            
            ll newHas = hasVal;
            
            if (i > 0) {
                newHas = 1;
            }
            if (newHas)
                res = max(solve(a, b, size, pos+1, i, newDec, newHas, newInc, dp)*i, res);
            else
                res = max(solve(a, b, size, pos+1, i, newDec, newHas, newInc, dp), res);
        }
        return dp[pos][prev][dec][hasVal][inc] = res;
    }
}

int main(){
    string a, b; cin >> a >> b;
    
    string origA = a;
    string temp = "";
    for (int i = 0; i < b.size() - a.size(); i++){
        temp += '0';
    }

    a = temp+a;
    vector dp(b.size()+1, vector(10, vector(2, vector(2, vector<ll>(2, -1)))));
    //cout << a << " " << b << endl;
    ll size = b.size();
    ll t = solve(a, b, size, 0, 0, 0, 0, 0, dp);
    //cout << t << endl;
    ll st = 1;
    string ans = "";
    for (int i = 0; i < b.size(); i++){
        for (int j = 9; j >= 0; j--){
            for (int k = 0; k < 2; k++){
                for (int l = 0; l < 2; l++){
                    for (int n = 0; n < 2; n++){
                        if (j == 0 and l == 0) continue;
                        if (j == 0 and l == 1){
                            //cout << i << " " << j << " " << k << " " << l << " " << n << endl;
                            ans += j+'0';
                            goto label;
                        }
                        if (dp[i+1][j][k][l][n] == -1) continue;
                        if (dp[i+1][j][k][l][n] == (t/j) and ((t%j) == 0 or t == 0)){
                            t /= j;
                            ans += j+'0';
                            goto label;
                        }
                    }
                }
            }
        }
        label:
            continue;
    }
    if (ans != ""){
        if (stoll(ans) < stoll(a))
            cout << stoll(a) << endl;
        else
            cout << stoll(ans) << endl;
    }
    else
        cout << 0 << endl;
    
    return 0;
    string testA = origA;
    string testB = b;
    ll tempA, tempB;
    ll tmp = 0;
    ll cor = -1;
    while (stoll(testA) != stoll(testB)+1){
        ll cur = 1;
        for (int i = 0; i < testA.size(); i++){
            cur *= testA[i]-'0';
        }

        if (cur >= tmp){
            tmp = cur;
            cor = stoll(testA);
        }

        testA = to_string(stoll(testA)+1);
    }
    cout << cor << endl;

}