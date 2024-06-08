#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
pair<ll, ll>,
null_type,
less<pair<ll ,ll>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;


int main(){
    int n, m; cin >> n >> m;
    vector<int> x;
    ll INF = 1000000000000000;
    for (int i = 0; i < n; i++) {
        int xi; long double pi; cin >> xi >> pi;
        x.push_back(xi);
    }

    vector<int> dp(n+1, 1);
    int ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (x[i] >= x[j]) {
                dp[i] = max(dp[i], dp[j]+1);
                ans = max(ans, dp[i]);
            }
        }
    }

    cout << n-ans << endl;




}