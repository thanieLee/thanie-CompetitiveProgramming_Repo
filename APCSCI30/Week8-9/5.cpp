#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
int n;
pair<int, int> getCoor(int diag, int y) {
    return {diag-y, y};
}


bool valid(ii &x){
    return 0 <= x.first and x.first < n and 0 <= x.second and x.second < n;
}


int main(){
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int t; cin >> t;
            g[i][j] = t;
        }
    }

    vector dp(2, vector(n, vector<int>(n, -1000000000)));
    vector<ii> delta = {{0, 1}, {1, 0}};

    dp[0][0][0] = g[0][0];
    for (int i = 0; i < 2*n-1; i++){
        for (int j = 0; j < n; j++){
            fill(dp[1][j].begin(), dp[1][j].end(), -1000000000);
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++){
            
                ii coord1 = {j, i-j};
                ii coord2 = {k, i-k};
                
                if (!valid(coord1) or !valid(coord2)) continue;
                for (ii c: delta){
                    for (ii v: delta){
                        ii new1 = {coord1.first+c.first, coord1.second+c.second};
                        ii new2 = {coord2.first+v.first, coord2.second+v.second};

                        if (!valid(new1) or !valid(new2)) continue;
                        int cnt;

                        if (new1 == new2) {
                            cnt = g[new1.first][new1.second];
                        } else {
                            cnt = g[new1.first][new1.second]+g[new2.first][new2.second];
                        }

                        //cout << dp[(i+1)%2][new1.first][new2.first] << " " << dp[i%2][coord1.first][coord2.first] + cnt << endl;
                        dp[1][new1.first][new2.first] = max(dp[0][coord1.first][coord2.first] + cnt, dp[1][new1.first][new2.first]);
                    }
                }
            }
        }

        swap(dp[0], dp[1]);
    }

    cout << dp[1][n-1][n-1] << endl;
}