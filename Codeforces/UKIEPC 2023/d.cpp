#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    deque<ll> arr;
    for (int i = 0; i < n; i++) {
        ll xi; cin >> xi;
        arr.push_back(xi);
    }
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    ll ans = 0;
    while (arr.size() >= 3) {
        ans += arr[1];
        arr.pop_back();
        arr.pop_front();
        arr.pop_front();
    }
    cout << ans << endl;
}