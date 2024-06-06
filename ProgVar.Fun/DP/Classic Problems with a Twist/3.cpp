#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, m; cin >> n >> m;
    vector<vector<ll>> graph(n, vector<ll>(m)); 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ll ai; cin >> ai;
            graph[i][j] = ai;
        }
    }

    vector<vector<ll>> dp1(n, vector<ll>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 and j == 0) {
                dp1[i][j] = graph[i][j];
            } else if (i == 0) {
                dp1[i][j] = dp1[i][j-1]+graph[i][j];
            } else if (j == 0) {
                dp1[i][j] = dp1[i-1][j]+graph[i][j];
            } else {
                dp1[i][j] = max(dp1[i-1][j], dp1[i][j-1]) + graph[i][j];
            }
        }
    }

    vector<vector<ll>> dp2(n, vector<ll>(m, 0));
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            if (i == n-1 and j == 0) {
                dp2[i][j] = graph[i][j];
            } else if (i == n-1) {
                dp2[i][j] = dp2[i][j-1]+graph[i][j];
            } else if (j == 0) {
                dp2[i][j] = dp2[i+1][j]+graph[i][j];
            } else {
                dp2[i][j] = max(dp2[i+1][j], dp2[i][j-1]) + graph[i][j];
            }
        }
    }

    vector<vector<ll>> dp3(n, vector<ll>(m, 0));
    for (int i = n-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            if (i == n-1 and j == m-1) {
                dp3[i][j] = graph[i][j];
            } else if (i == n-1) {
                dp3[i][j] = dp3[i][j+1]+graph[i][j];
            } else if (j == m-1) {
                dp3[i][j] = dp3[i+1][j]+graph[i][j];
            } else {
                dp3[i][j] = max(dp3[i+1][j], dp3[i][j+1]) + graph[i][j];
            }
        }
    }

    vector<vector<ll>> dp4(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = m-1; j >= 0; j--) {
            if (i == 0 and j == m-1) {
                dp4[i][j] = graph[i][j];
            } else if (i == 0) {
                dp4[i][j] = dp4[i][j+1]+graph[i][j];
            } else if (j == m-1) {
                dp4[i][j] = dp4[i-1][j]+graph[i][j];
            } else {
                dp4[i][j] = max(dp4[i-1][j], dp4[i][j+1]) + graph[i][j];
            }
        }
    }

    
    ll ans = 0;
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-1; j++) {
            ll case1 = dp1[i-1][j]+dp2[i][j-1]+dp3[i+1][j]+dp4[i][j+1];
            ll case2 = dp1[i][j-1]+dp2[i+1][j]+dp3[i][j+1]+dp4[i-1][j];

            ans = max(ans, max(case1, case2));
        }
    }

    cout << ans << endl;
}