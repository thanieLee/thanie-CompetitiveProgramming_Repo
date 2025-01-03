#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


int is_taro(int current, int total) {
    return (current%2) == (total%2);
}

int main(){
    int n; cin >> n;
    vector<ll> arr;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        arr.push_back(x);
    }

    vector<vector<ll>> ans(n+1, vector<ll>(n+1, 0));

     
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j+i <= n; j++) {
            if (is_taro(i, n)) {
                ans[j][j+i] = max(ans[j+1][j+i] + arr[j], ans[j][j+i-1] + arr[j+i-1]);
            } else {
                ans[j][j+i] = min(ans[j+1][j+i] - arr[j], ans[j][j+i-1] - arr[j+i-1]);
            }
        }
    }

    // for (int i = 0; i < n; i++) {
    //     cout << ans[i][i+1] << " ";
    // }

    cout << ans[0][n] << endl;
}