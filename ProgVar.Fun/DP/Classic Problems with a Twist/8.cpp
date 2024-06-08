#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
    }

    vector<int> dp(1000001, 1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = a[i]*2;
        while (cur <= 1000000) {
            dp[cur] = max(dp[cur], dp[a[i]]+1);
            cur += a[i];
        }
        ans = max(ans, dp[a[i]]);
    }
    
    cout << ans << endl;
}