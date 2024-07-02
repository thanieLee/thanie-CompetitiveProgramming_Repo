#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, m; cin >> n >> m;
    vector<int> perm;
    for (int i = 1; i <= n; i++) {
        perm.push_back(i);
    }

    vector<vector<int>> conditions;
    for (int i = 0; i < m; i++) {
        int xi, yi, zi; cin >> xi >> yi >> zi;
        conditions.push_back({xi, yi, zi});
    }

    
    ll ans = 0;
    do {
        bool can = true;

        for (int i = 0; i < m; i++) {
            int xi = conditions[i][0], yi = conditions[i][1], zi = conditions[i][2];
            int cnt = 0;
            for (int j = 0; j < xi; j++) {
                if (perm[j] <= yi) cnt++;
            }

            if (cnt > zi) can = false;
        }

        if (can)  {
            for (int i : perm) {
                cout << i << " ";
            }
            cout << endl;
            ans++;
        }
    } while (next_permutation(perm.begin(), perm.end()));
    cout << ans << endl;
}