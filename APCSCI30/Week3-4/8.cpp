#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    vector dp(3, vector(2, vector<ll>(2, 0)));

    dp[0][0][0] = 1;
    dp[0][1][0] = 1;
    dp[0][0][1] = 1;

    for (int i = 1; i < 3; i++){
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++){
                if (k == 1 and j == 1) continue;
                dp[i][j][k] += dp[i-1][0][0];
                dp[i][j][k] += dp[i-1][1][0];
                dp[i][j][k] += dp[i-1][0][1];
                
            }
        }
    }

    ll cnt = 0;
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            if (i == 1 and j == 1) continue;
            cnt += dp[2][i][j];
        }
    }
    cnt -= dp[2][0][0];
    cnt += dp[1][1][0];
    cnt += dp[1][0][1]; 
    cout << cnt << endl;
}