#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int t; cin >> t;
    while (--t){
    ll n, k; cin >> n >> k;
    ll cnt = 0;
    if (k == 0) {
        continue;
        cout << n*n << endl;
        continue;
    }
    for (ll i = 1; i <= n; i++){
        if (i-k <= 0) continue;

        int num = i-k;
        int end = n - (n%i);
        //cout << end << " " << num << endl;
        int sm = (end/i) * num;
        if ((n%i) != 0)
            sm += max(0ll, (n%i)-(k-1)); 
        cnt += sm;
        //cout << i << " " << (end/i) * num << " " <<  max(0ll, (n%i)-(k-1)) <<  endl;
    }

    int brute = 0;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if ((i % j) >= k) {
                brute++;
            }
        }
    }
    if (cnt != brute)
        cout << cnt << " " << brute << " " << n << " " << k << endl;
    }
}