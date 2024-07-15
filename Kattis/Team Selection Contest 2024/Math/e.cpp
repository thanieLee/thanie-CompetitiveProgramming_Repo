#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

int main(){
    int n; cin >> n;
    vector<ll> x, y;
    map<ll, map<ll, bool>> is_point;
    for (int i = 0; i < n; i++) {
        ll xi, yi; cin >> xi >> yi;
        x.push_back(xi);
        y.push_back(yi);

        is_point[xi][yi] = true;
    }

    ll ans = 0;

    vector<ll> deltax = {0, 1118, 1680, 2018};
    vector<ll> deltay = {2018, 1680, 1118, 0};

    vector<ll> sign_x = {1, -1, 1, -1};
    vector<ll> sign_y = {-1, -1, 1, 1};
    
    for (int i = 0; i < n; i++) {
        ll cur_x = x[i];
        ll cur_y = y[i];

        for (int j = 0; j < 4; j++) {
            for (int l = 0; l < 4; l++) {
                if ((j == 0 and l == 1) or (j == 0 and l == 3)) continue;
                if ((j == 3 and l == 0) or (j == 3 and l == 2)) continue;
                ll new_x = cur_x + deltax[j]*sign_x[l];
                ll new_y = cur_y + deltay[j]*sign_y[l];

                if (is_point.find(new_x) != is_point.end()) {
                    if (is_point[new_x].find(new_y) != is_point[new_x].end()) {
                        ans++;
                    }
                }
            }
        }
    }

    cout << ans/2 << endl;

}