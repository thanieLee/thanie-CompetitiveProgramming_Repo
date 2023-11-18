#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef pair<int, int> ii;
typedef long long int ll;
typedef vector<ll> vi;
#define m 1000000007

int total(int layer){
    return ((layer) * (layer+1))/2;
}

int MOD(int x){
    return ((x%m)+m)%m;
}

int main(){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    int r, g; cin >> r >> g;
    vector dp(2, vector(2, vector<int>(r+1, 0)));

    if (r > 0)
        dp[0][0][1] = 1;
    if (g > 0)
        dp[0][1][0] = 1;

    for (int i = 1; i < 900; i++){
        int cur = -1;
        for (int j = 0; j < 2; j++){
            for (int k = 0; k <= r; k++){
                dp[1][j][k] = 0;
            }
        }
        for (int k = 0; k <= r; k++){
            int all = total(i);
            if (k + (i+1) <= r) {
                if (g-((all - k)) >= 0){
                    dp[1][0][k + (i+1)] += dp[0][0][k];
                    dp[1][0][k + (i+1)] += dp[0][1][k];
                    
                    dp[1][0][k + (i+1)] %= m;
                    
                    cur = max(cur, dp[1][0][k + (i+1)]);
                }
            }

            if (g-((all - k)) - (i+1) >= 0) {
                dp[1][1][k] += dp[0][0][k];
                dp[1][1][k] += dp[0][1][k];
                dp[1][1][k] = dp[1][1][k]%m;
                cur = max(cur, dp[1][1][k]);
            }
        }

        //cout << cur << endl;
        if (cur <= 0) {
            break;
        }
        swap(dp[0], dp[1]);
    }


    int cnt = 0;
    for (int j = 0; j < 2; j++){
        for (int k = 0; k <= r; k++){
            cnt += dp[0][j][k]%m;
            cnt = cnt%m;
        }
    }
    cout << cnt%m << endl;
    gettimeofday(&end, NULL);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - 
                              start.tv_usec)) * 1e-6;

    cout << fixed << time_taken << setprecision(5) << endl;
}