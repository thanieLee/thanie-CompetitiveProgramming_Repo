#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll f(ll a, ll b, ll c) {
    return 2023*a*pow(b, 3) + 1858*a*b*c + 1084670664*pow(a, 2)-2024*pow(b, 2)*pow(c, 2) - 1966*pow(b, 4)*c - 36051705*pow(c, 3);
}

int main(){
    vector<ll> sol1 = {13, 42, 14};
    vector<ll> sol2 = {17, 69, 7};


    for (ll i = 1; i <= 213484; i++) {
        cout << sol1[0]*i*i*i << " " << sol1[1]*i << " " << sol1[2]*i*i << endl;
        cout << sol2[0]*i*i*i << " " << sol2[1]*i << " " << sol2[2]*i*i << endl;
    }

    cout << sol1[0]*213485*213485*213485 << " " << sol1[1]*213485 << " " << sol1[2]*213485*213485 << '\n';
}