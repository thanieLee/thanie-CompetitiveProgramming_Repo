#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll h, w, k; cin >> h >> w >> k;
    vector<vector<ll>> graph(h, vector<ll>(w, 0));
    for (int i = 0; i < h; i++) {
        string s; cin >> s;
        for (int j = 0; j < w; j++) {
            char c = s[j];
            graph[i][j] = c-'0';
        }
    }

    vector<vector<ll>> cum(h+1, vector<ll>(w+1, 0));
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cum[i][j] = cum[i][j-1]+cum[i-1][j]-cum[i-1][j-1]+graph[i-1][j-1];
        }
    }

    ll ans = 100000;
    for (int i = 0; i < 1<<(h-1); i++) {
        //cout << bitset<9>(i) << endl;
        if (i == 0) {
            ll prev = 0;
            ll cnt = 0;
            for (int j = 1; j <= w; j++) {
                //cout << cum[h][j] << " " << cum[h][prev] << endl;
                if (cum[h][j]-cum[h][prev] > k) {
                    cnt++;
                    if (prev == j-1) goto exit;
                    prev = j-1;
                }
            }
            ans = min(cnt, ans);
            //cout << cnt << endl;
        } else {
            vector<ll> check = {0};
            ll total = 0;
            for (int j = 0; j < h-1; j++) {
                if (i & (1<<j)) {
                    check.push_back(j+1);
                    total++;
                }
            }
            check.push_back(h);

            ll point = 0;
            ll cnt = 0;
            for (int j = 1; j <= w; j++) {
                ll can = true;

                for (int l = 0; l < check.size()-1; l++) {
                    ll cur = check[l+1], prev = check[l];
                    //cout << cur << " " << j << " " << prev << " " << point << endl;
                    //cout << cum[cur][j] << " " << cum[prev][point] << endl;
                    if (cum[cur][j] - cum[cur][point] - cum[prev][j] + cum[prev][point] > k) {
                        can = false;
                    }
                }
                //cout << endl;

                if (!can) {
                    cnt++;
                    if (point == j-1) goto exit;
                    point = j-1;
                }
            }

            ans = min(ans, cnt+total);
            //cout << "ans: " << cnt << " " << total << endl;
        }

        exit:
            continue;
    }

    cout << ans << endl;
}