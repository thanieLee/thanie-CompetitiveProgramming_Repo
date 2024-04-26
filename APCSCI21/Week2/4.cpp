#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
vector<int> arr;

bool cmp(int u, int v) {
    return arr[u] < arr[v];
} 

int main(){
    int n; cin >> n;
    for (int i = 0; i < 1<<n; i++){
        int x; cin >> x;
        arr.push_back(x);
    }

    vector<pll> dp(1<<n+1, {-1, -1});
    dp[0] = {0, 0};
    for (int i = 1; i < 1<<n; i++) {
        set<int> pos;
        pos.insert(i);
        for (int j = 0; j < n; j++) {
            if ((i & (1<<j)) == 0) continue;
            int f = dp[i & ~(1<<j)].first, s = dp[i & ~(1<<j)].second;
            if (f > -1)
                pos.insert(f);
            if (s > -1)
                pos.insert(s);
        }
        pos.insert(dp[i-1].first);
        pos.insert(dp[i-1].second);
        int l1 = -1, l2 = -1, temp = 0;
        for (auto it1 = pos.begin(); it1 != pos.end(); it1++) {
            for (auto it2 = it1; it2 != pos.end(); it2++) {
                if (it2 == it1) continue;
                if (min(*it1, *it2) < 0) continue;
                if ((*it1 | *it2) > i) continue;
                if (arr[*it1]+arr[*it2] > temp) {
                    temp = arr[*it1]+arr[*it2];
                    l1 = *it1;
                    l2 = *it2;
                }
            }
        }
        dp[i] = {l1, l2};
    }

    for (int i = 1; i < 1<<n; i++) {
        cout << arr[dp[i].first]+arr[dp[i].second] << endl;
    }
}