#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;


struct tupe {
    int first, second, idx;

    tupe(int f, int s, int i) {
        first = f;
        second = s;
        idx = i;
    }
};



bool cmp(tupe &x, tupe &y) {
    if (x.first == y.first and x.second == y.second) {
        return x.idx < y.idx;
    } else if (x.first == y.first) {
        return x.second < y.second;
    }
    return x.first < y.first;
}


int main(){
    int n, w, h; cin >> n >> w >> h;
    vector<int> dp(n+2, 0);
    vector<tupe> arr = {};
    for (int i = 0; i < n; i++) {
        int wi, hi; cin >> wi >> hi;
        arr.push_back({wi, hi, i+1});
    }
    dp[0] = 0;
    sort(arr.begin(), arr.end(), cmp);
    arr.push_back({10000000, 10000000, n+1});
    reverse(arr.begin(), arr.end());
    arr.push_back({w, h, 0});
    reverse(arr.begin(), arr.end());
    for (int i = 0; i <= n+1; i++) {
        tupe cur = arr[i];

        for (int j = i+1; j <= n+1; j++) {
            tupe next = arr[j];
            if (next.idx == 0 or (dp[i] == 0 and i != 0)) continue;
            if (i == 0 and j == n+1) continue;
            if (cur.first < next.first and cur.second < next.second) {
                dp[j] = max(dp[j], dp[i]+1);
            }
        }
    }

    vector<int> ans = {};
    int curSize = dp[n+1];
    int curIdx = n+1;
    if (curSize == 0) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = n; i >= 1; i--) {
        if (dp[i] != 0 and dp[i]+1 == curSize and (arr[curIdx].first > arr[i].first and arr[curIdx].second > arr[i].second)) {
            curIdx = i;
            curSize--;
            if (i != 0)
                ans.push_back(arr[i].idx);
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}