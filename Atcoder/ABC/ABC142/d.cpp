#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<ll> divisors(ll x){
    vector<ll> output;

    for (int i = 1; i <= ceil(sqrt(x)); i++){
        if (x%i == 0){
            if (x/i == i){
                output.push_back(i);
            } else {
                output.push_back(x/i);
                output.push_back(i);
            }
        }
    }

    return output;
}

ll gcd(ll a, ll b){
    if (a == 0){
        return b;
    } else {
        return gcd(b%a, a);
    }
}
int main(){
    ll a, b; cin >> a >> b;

    vector<ll> aDiv = divisors(a);
    vector<ll> bDiv = divisors(b);
    set<ll> divs;
    ll ans = 0;
    for (int i = 0; i < aDiv.size(); i++){
        for (int j = 0; j < bDiv.size(); j++){
            if (aDiv[i] == bDiv[j]) divs.insert(aDiv[i]);
        }
    }
    
    vector<ll> div;
    
    for (auto it = divs.begin(); it != divs.end(); it++){
        bool can = true;
        for (int i = 0; i < div.size(); i++){
            if (gcd(*it, div[i]) != 1) can = false;
        }
        if (can)
            div.push_back(*it);
    }
    cout << div.size() << endl;
    
}