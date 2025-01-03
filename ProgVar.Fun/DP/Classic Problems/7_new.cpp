#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll MOD = 1000000007;

ll mod(ll x) {
    return ((x%MOD)+MOD)%MOD;
} 

int main(){
    ll h, w; cin >> h >> w;
    vector<vector<bool>> graph(h, vector<bool>(w, true));
    vector<vector<ll>> ans(h, vector<ll>(w, 0));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char c; cin >> c;
            if (c == '#') {
                graph[i][j] = false;
            }
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i == 0 and j == 0) {
                ans[i][j] = 1;
            } else {
                if (i > 0) {
                    if (graph[i-1][j]) {
                        ans[i][j] += ans[i-1][j];
                        ans[i][j] = mod(ans[i][j]);
                    }
                }

                if (j > 0) {
                    if (graph[i][j-1]) {
                       ans[i][j] += ans[i][j-1];
                       ans[i][j] = mod(ans[i][j]);
                    }
                }
            }
        }
    }

    cout << ans[h-1][w-1] << endl;

}