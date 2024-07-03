#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll n, k; cin >> n >> k;
    vector<int> colors;
    for (int i = 0; i < n; i++) {
        int ci; cin >> ci;
        colors.push_back(ci);
    }

    map<int, int> col;

    for (int i = 0; i < k; i++) {
        if (col.find(colors[i]) == col.end()) {
            col[colors[i]] = 1;
        } else {
            col[colors[i]]++;
        }
    }

    int ans = col.size();

    for (int i = k; i < n; i++) {
        col[colors[i-k]]--;
        if (col[colors[i-k]] == 0) {
            col.erase(colors[i-k]);
        }
        
        if (col.find(colors[i]) == col.end()) {
            col[colors[i]] = 1;
        } else {
            col[colors[i]]++;
        }

        ans = max(ans, (int)col.size());
    }

    cout << ans << endl;
}