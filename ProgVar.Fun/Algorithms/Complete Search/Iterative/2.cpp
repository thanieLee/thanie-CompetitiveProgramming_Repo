#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<int> x;
    for (int i = 0; i < n; i++ ) {
        int xi; cin >> xi;
        x.push_back(xi);
    }
    int ans = 1000000000;
    for (int p = -1000; p <= 1000; p++){
        int cost = 0;
        for (int i = 0; i < n; i++) {
            cost += pow(x[i]-p, 2);
        }
        ans = min(cost, ans);
    }
    cout << ans << endl;
}