#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


map<vector<bool>, bool> has;
bool win(vector<bool> coins) {

    if (has.find(coins) != has.end()) {
        return has[coins];
    }

    bool lose = true;
    if (coins.size() == 0) return false;
    for (bool c : coins) {
        if (c == true) lose = false;
    }

    if (lose) return false;

    bool isLose = false;
    int ni = coins.size();
    for (int i = 0; i < ni; i++) {
        if (coins[i] == true) {
            vector<bool> newCoins = coins;
            newCoins[(i-1+ni)%ni] = !newCoins[(i-1+ni)%ni];
            newCoins[(i+1+ni)%ni] = !newCoins[(i+1+ni)%ni];
            newCoins.erase(next(newCoins.begin(), i));
            bool nex = win(newCoins);
            if (!nex) isLose = true;
        }
    }

    has[coins] = isLose;
    return isLose;
}


int main(){
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<bool> coin(n);
        for (int i = 0; i < n; i++) {
            char c; cin >> c;
            if (c == 'U') {
                coin[i] = true;
            } else {
                coin[i] = false;
            }
        }


        if (win(coin)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}