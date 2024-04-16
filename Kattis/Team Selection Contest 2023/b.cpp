#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll n; cin >> n;
    vector<ll> arr;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        arr.push_back(x);
    }
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    ll curCnt = 1;
    ll curSum = arr[0];
    ll running = 0;
    for (int i = 1; i < n; i++) {
        if (running >= curSum) {
            curSum += running;
            curCnt = i;
            running = arr[i];
        } else {
            running += arr[i];
        }
    }
    cout << curCnt << endl;
}