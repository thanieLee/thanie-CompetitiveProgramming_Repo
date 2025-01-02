#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll n, c; cin >> n >> c;
    vector<ll> arr(n);
    ll l = ceil(log2(n*2 + 1));
    vector<vector<ll>>  jump(n*2+1, vector<ll>(l+1, 2*n));
    set<pair<ll, ll>> test;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        arr[i] = x;
    }

    ll run = 0;
    for (int i = 0; i < 2*n; i++) {
        run += arr[i%n];
        test.insert({run, i});
    }

    test.insert({100000000000, 2*n-1});
    run = 0;
    for (int i = 0; i < 2*n; i++) {
        // int idx_cur = i;
        // int temp = c;
        // while (temp > 0 and idx_cur < i+n) {
        //     temp -= arr[idx_cur%n];
        //     idx_cur++;
        //     if (idx_cur == 2*n) break;
        // }

        auto ans = test.lower_bound({run+c, -1});
        run += arr[i%n];
        //cout << idx_cur << " " << ans->second << endl;
        jump[i][0] = ans->second+1;
    }
    for (int j = 1; j <= l; j++){
        for (int i = 0; i < 2*n; i++) {
            jump[i][j] = jump[jump[i][j-1]][j-1];
            //cout << i << " " << j-1 << " " << jump[i][j-1] << " " << jump[jump[i][j-1]][j-1] << endl;
        }
    }

    for (int i = 0; i < n; i++) {
        ll cnt = 0;
        int cur = i;
        for (int j = l; j >= 0; j--) {
            //cout << i << " " << cur << " " << j << " " << jump[cur][j] << endl;
            if (jump[cur][j] < i+n) {
                cnt += pow(2, j);
                cur = jump[cur][j];
            }
        }

        cout << cnt << " ";
    }
}