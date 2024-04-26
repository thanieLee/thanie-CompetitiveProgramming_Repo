#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

int main(){
    int n; cin >> n;
    for (int i = 1; i < 1<<n; i++) {
        cout << bitset<6>(i) << endl;
        for (int j = 0; j < 1<<n; j++) {
            for (int k = j+1; k < 1<<n; k++) {
                if ((j | k) <= i) {
                    cout << bitset<6>(j) << " " << bitset<6>(k) << endl;
                }
            }
        }
        cout << endl;
    }
}