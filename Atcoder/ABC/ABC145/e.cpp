    #include <bits/stdc++.h>
    using namespace std;
    typedef long long int ll;
    typedef pair<int, int> pii;


    bool cmp (pii &x, pii &y) {
        return x.first < y.first;
    }

    int main(){
        int n, t; cin >> n >> t;

        vector<int> a, b;
        vector<pii> ab;
        for (int i = 0; i < n; i++) {
            int ai, bi; cin >> ai >> bi;
            a.push_back(ai);
            b.push_back(bi);
            ab.push_back({ai, bi});
        }

        sort(ab.begin(), ab.end(), cmp);

        vector<vector<int>> dp(n+1, vector<int>(t+3001, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= t+3000; j++) {
                dp[i][j] = dp[i-1][j];
            }

            for (int j = ab[i-1].first; j <= t-1+ab[i-1].first; j++) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-ab[i-1].first]+ab[i-1].second);
            }
        }

        int mx = 0;
        for (int i = 0; i <= t+3000; i++) {
            mx = max(mx, dp[n][i]);
        }
        cout << mx << endl;
    }