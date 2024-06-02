#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll n, x; cin >> n >> x;
    vector<ll> coins;
    for (int i = 0; i < n; i++) {
        ll ci; cin >> ci;
        coins.push_back(ci);
    }

    sort(coins.begin(), coins.end());

    vector<int> pos(1000001, 10000000);
    pos[0] = 0;
    
    for (int i = 1; i <= 1000000; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] > i) continue;
            pos[i] = min(pos[i], pos[i-coins[j]]+1);
        }
    }
    //cout << pos[1] << " " << pos[10] << endl;
    if (pos[x] == 10000000) {
        cout << -1 << endl;
    } else {
        cout << pos[x] << endl;
    }
    
}