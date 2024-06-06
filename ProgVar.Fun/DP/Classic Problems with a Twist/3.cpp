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

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            cout << dp1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            cout << dp2[i][j] << " ";
        }
        cout << endl;
    }

}