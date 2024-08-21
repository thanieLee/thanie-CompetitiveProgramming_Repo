#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, m; cin >> n >> m;
    vector<vector<char>> graph(n, vector<char>(m));
    vector<vector<vector<vector<ll>>>> dp(n, vector(m, vector(3, vector<ll>(2, 0))));
    map<char, int> alpha_conv;
    alpha_conv['I'] = 0;
    alpha_conv['C'] = 1;
    alpha_conv['P'] = 2;
    
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            graph[i][j] = s[j];
        }
    }

    for (int i = 0; i < m; i++) {
        if (graph[0][i] == '?') {
            for (int j = 0; j < 3; j++) {
                dp[0][i][j][0] = 1;
            }
        } else {
            dp[0][i][alpha_conv[graph[0][i]]][0] = 1;
        }
    }

    if (graph[1][0] == '?') {
        for (int i = 0; i < 3; i++) {
            dp[1][0][i][0] = 1;
        }
    } else {
        dp[1][0][alpha_conv[graph[1][0]]][0] = 1;
    }

    for (int i = 1; i < n; i++){
        for (int j = 1; j < m; j++) {
            // no icpc yet
            for (int top_left = 0; top_left < 3; top_left++) {
                for (int top_right = 0; top_right < 3; top_right++) {
                    for (int bottom_left = 0; bottom_left < 3; bottom_left++) {
                        for (int bottom_right = 0; bottom_right < 3; bottom_right++) {
                            if (top_left == 0 and top_right == 1 and bottom_left == 2 and bottom_right == 1) continue;
                            if (graph[i][j] != '?' and bottom_right != alpha_conv[graph[i][j]]) continue;
                            ll top_left_val = dp[i-1][j-1][top_left][0];
                            ll top_right_val = dp[i-1][j][top_right][0];
                            ll bottom_left_val = dp[i][j-1][bottom_left][0];
                            dp[i][j][bottom_right][0] += top_left_val * top_right_val * bottom_left_val;
                        }
                    }
                }
            }

            // currently making an icpc on this one (no previous icpc)
            if (graph[i][j] == 1 or graph[i][j] == '?') {
                dp[i][j][1][1] += dp[i-1][j-1][0][0] * dp[i][j-1][2][0] * dp[i-1][j][1][0];
                if (i == n-1 and j == m-1) {
                    cout << dp[i-1][j-1][0][0] << " " << dp[i][j-1][2][0] << " " << dp[i-1][j][1][0] << endl;
                    cout << dp[i][j][1][1] << endl;
                }
            }


            // transferring previous icpc
            for (int top_left = 0; top_left < 3; top_left++) {
                for (int top_right = 0; top_right < 3; top_right++) {
                    for (int bottom_left = 0; bottom_left < 3; bottom_left++) {
                        for (int bottom_right = 0; bottom_right < 3; bottom_right++) {
                            if (graph[i][j] != '?' and bottom_right != alpha_conv[graph[i][j]]) continue;
                            ll top_left_val = dp[i-1][j-1][top_left][1];
                            ll top_right_val = dp[i-1][j][top_right][1];
                            ll bottom_left_val = dp[i][j-1][bottom_left][1];
                            dp[i][j][bottom_right][1] += top_left_val * top_right_val * bottom_left_val;
                        }
                    }
                }
            }

        }
    }

    ll ans = 0;
    cout << dp[1][0][1][0] << endl;
    for (int i = 0; i < 3; i++) {
        cout << dp[n-1][m-1][i][1] << endl;
        ans += dp[n-1][m-1][i][1];
    }

    cout << ans << endl;
}