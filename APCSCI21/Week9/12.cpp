#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
vector<ll> deltax = {0, 1};
vector<ll> deltay = {1, 0};
ll r, c;
vector<vector<ll>> val;
vector<vector<vector<ll>>> dp;


ll dfs(ll x, ll y, ll curItems){
    //cout << x << " " << y << " " << curItems << endl;
    if (dp[x][y][curItems] != -1) {
        return dp[x][y][curItems];
    }
    if (x == r and y == c) {
        if (curItems < 3) {
            return dp[x][y][curItems] = val[x][y];
        }
        return dp[x][y][curItems] = 0;
    } else {
        ll ans1 = 0;
        if (curItems < 3 and val[x][y] > 0) {
            ans1 = 0;
            for (int i = 0; i < 2; i++) {
                ll newx = x+deltax[i];
                ll newy = y+deltay[i];

                if (0 <= newx and newx < r and 0 <= newy and newy < c) {
                    if (newx == x)
                        ans1 = max(ans1, dfs(newx, newy, curItems+1));
                    else
                        ans1 = max(ans1, dfs(newx, newy, 0));
                }
            }
            ans1 += val[x][y];
        }

        ll ans2 = 0;
        for (int i = 0; i < 2; i++) {
            ll newx = x+deltax[i];
            ll newy = y+deltay[i];

            if (0 <= newx and newx < r and 0 <= newy and newy < c) {
                if (newx == x)
                        ans1 = max(ans1, dfs(newx, newy, curItems));
                    else
                        ans1 = max(ans1, dfs(newx, newy, 0));
            }
        }
        return dp[x][y][curItems] = max(ans1, ans2);
    }
}

int main(){
    ll k; cin >> r >> c >> k;
    val.resize(r+1, vector<ll>(c+1, 0));
    dp.resize(r+1, vector<vector<ll>>(c+1, vector<ll>(4, -1)));
    for (int i = 0; i < k; i++) {
        ll ri, ci, ki; cin >> ri >> ci >> ki; ri--; ci--;
        val[ri][ci] = ki;
    }

    cout << dfs(0, 0, 0) << endl;
}