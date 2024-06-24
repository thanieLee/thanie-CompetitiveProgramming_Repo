#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<int> x, x_orig;
    for (int i = 0; i < n; i++) {
        int xi; cin >> xi;
        x.push_back(xi);
        x_orig.push_back(xi);
    }
    sort(x.begin(), x.end());

    for (int i = 0; i < n; i++) {
        auto ptr = lower_bound(x.begin(), x.end(), x_orig[i]);
        int idx = ptr-x.begin();
        if (idx <= (n-1)/2) {
            cout << x[((n-1)/2)+1] << endl;
        } else {
            cout << x[((n-1)/2)] << endl;
        }
    }
}