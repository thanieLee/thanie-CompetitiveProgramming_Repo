#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;



int main(){
    int n; cin >> n;
    vector<ll> a;
    for (int i = 0; i < n; i++) {
        ll ai; cin >> ai;
        a.push_back(ai);
    }


    vector<vector<ll>> sums(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
        ll cnt = 0;
        for (int j = i; j < n; j++) {
            cnt += a[j];
            sums[i][j] = cnt;
        }
    }

    cout << sums[1][3] << endl;
}