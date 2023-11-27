#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll LSB(ll n){
    ll idx = 0;
    while ((n&1) == 0){
        n>>=1;
        idx++;
    }
    return 1<<idx;
}

int main(){
    ll test = 4;
    cout << LSB(test) << endl;
}