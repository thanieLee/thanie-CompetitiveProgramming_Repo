#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
vector<ll> x, y, s;
int n;
ld slow;

vector<vector<ld>> dists;
vector<ld> slows;

ld dist(ll x1, ll y1, ll x2, ll y2) {
    return (ld)sqrt((ld)pow(x1-x2, 2ll) + (ld)pow(y1-y2, 2ll));
}

bool can(ld M) {
    vector<vector<ld>> dp(1<<n, vector<ld>(16, 100000000.0l));

    for (int msk = 1; msk < (1<<n); msk++) {
        int len = __builtin_popcount(msk);
        if (len == 1) {
            int msb = -1;
            for (int i = 0; i < n; i++) {
                if (msk & (1<<i)) msb = i;
            }

            ld time_with_speed = dist(0ll, 0ll, x[msb], y[msb])/M;
            if (time_with_speed <= s[msb]) dp[msk][msb] = time_with_speed;
        } else {
            vector<int> all;
            for (int i = 0; i < n; i++) {
                if (msk & (1<<i)) all.push_back(i);
            }
            for (int i : all) {
                if (!(msk & (1<<i))) continue;
                int prev = msk & ~(1<<i);
                for (int j : all) {
                    if (!(msk & (1<<j)) or i == j) continue;
                    if (dp[prev][j] == 100000000.0) continue;
                    ld old_time = dp[prev][j];
                    ld new_time = dists[i][j]/(M*slows[len-1]);

                    if (old_time + new_time <= s[i]) dp[msk][i] = min(dp[msk][i], old_time + new_time);
                }
            }
        }
    }
    
    bool ans = false;
    for (int i = 0; i < n; i++) {
        if (dp[(1<<n)-1][i] != 100000000.0) ans = true;
    }

    return ans;
}


bool can_brute(ld M, vector<int> &perm) {
    ld total_time = dist(0, 0, x[perm[0]], y[perm[0]])/M;
    for (int i = 1; i < n; i++) {
        int cur = perm[i];
        int prev = perm[i-1];
        total_time += dists[cur][prev]/(M*slows[i]);
    }

    bool can = true;
    for (int i = 0; i < n; i++) {
        if (total_time > s[i]) can = false;
    }
    
    return can;
}

ld bsearch(ld L, ld R) {
    int cnt = 0;
    while (R-L > 0.0000001 and cnt <= 500) {
        ld M = (R-L)/2l + L;
        cnt++;
        if (can(M)) { 
            R = M;
        } else {
            L = M;
        }
    }
    return L;
}

int main(){
    cin >> n;

    dists.resize(n, vector<ld>(n));
    for (int i = 0; i < n; i++) {
        ll xi, yi, si; cin >> xi >> yi >> si;
        x.push_back(xi);
        y.push_back(yi);
        s.push_back(si);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            ld dis = dist(x[i], y[i], x[j], y[j]);
            dists[i][j] = dis;
            dists[j][i] = dis;
        }
    }
    
    
    string slo; cin >> slo;
    ll num = stoll(slo.substr(1, 2));
    slow = num/100.0l;
    for (int i = 0; i <= n; i++) {
        slows.push_back(pow(slow, i));
    }
    ld ans = bsearch(0, 10000000);
    cout << setprecision(12) << ans << endl;
    

}