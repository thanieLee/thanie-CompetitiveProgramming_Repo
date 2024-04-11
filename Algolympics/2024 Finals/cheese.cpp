#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll MOD = 998244353;

int main(){
    cout << "vector<ll> fact = {";
    ll cur = 1;
    ll n = 300000;
    for (int i = 0; i < MOD; i++) {
        if (i != 0) {
            cur *= i;
            cur %= MOD;
        }
        if ((i%(31595*6)) == 0) {
            cout << cur << ", ";
        }
    }
    cout << "}" << endl;
}