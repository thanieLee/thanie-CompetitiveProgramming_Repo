#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int h, w, a, b; cin >> h >> w >> a >> b;

    vector dp(w+1, vector((1<<h)+1, vector(a+1, vector<int>(b+1, 0))));
    dp[1][0][0][0] = 1;
    for (int msk = 0; msk < (1<<h); msk++) {
        cout << bitset<2>(msk) << endl;
        for (int i = 1; i <= h; i++) {
            if ((msk & (1<<(i-1)))) {
                for (int j = b; j >= 1; j--) {
                    dp[1][msk][0][j] += dp[1][msk & ~(1<<(i-1))][0][j-1];
                }
            }
        }

        for (int i = 1; i < h; i++) {
            if ((msk & (1<<(i-1))) > 0 and (msk & (1<<(i))) > 0) {
                for (int j = 0; j <= b; j++) {
                    for (int k = 1; k <= a; k++) {
                        cout << (msk | (1<<(i-1)) | (1<<(i))) << endl;
                        dp[1][msk][k][j] += dp[1][msk & ~(1<<(i-1)) & ~(1<<(i))][k-1][j];
                    }
                }
            }   
        }
    }

    cout << dp[1][3][0][2] << endl;
}