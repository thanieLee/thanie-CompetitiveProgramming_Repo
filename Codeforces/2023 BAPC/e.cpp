#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<ll> s, p, e, a;
vector<vector<ll>> freetime;
vector<vector<ll>> dp;
int n; 
int ans = 0;

int main(){
    cin >> n;
    s.resize(n+2, 0); p.resize(n+2, 0); e.resize(n+2, 0); a.resize(n+2, 0);
    freetime.resize(n+2, vector<ll>(n+2, 0));
    dp.resize(n+2, vector<ll>(n+2, -1));


    for (int i = 1; i < n+1; i++){
        ll si, pi, ei, ai; cin >> si >> pi >> ei >> ai;
        s[i] = si;
        p[i] = pi;
        e[i] = ei;
        a[i] = ai;
    }

    for (int i = 0; i <= n; i++) {
        for (int j = i+1; j <= n; j++){
            freetime[i][j] = freetime[i][j-1] + (s[j]-e[j-1]);
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++){
        for (int j = 0; j < n; j++){
            if (dp[i-1][j] > -1)
                dp[i][j] = max(dp[i-1][j]+freetime[i-1][i], dp[i][j]);

            if (dp[i-1][j]+freetime[i-1][i] >= a[i] and dp[i-1][j] > -1) {
                dp[i][j+1] = max(dp[i][j+1], dp[i-1][j]+freetime[i-1][i]-a[i]+e[i]-p[i]);
            }
        }
    }

    
    for (int i = n; i >= 0; i--){
        if (dp[n][i] > -1) {
            cout << i << endl;
            return 0;
        }
    }
}