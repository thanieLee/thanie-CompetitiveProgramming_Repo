#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<ll> arr;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        arr.push_back(x);
    }

    vector<ll> longest(n, 1);
    ll ans = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i-1]) {
            longest[i] += longest[i-1];
        }
    }
    
    int cur = -1;
    int next = -1;
    for (int i = 1; i < n; i++) {
        if (arr[i] <= arr[i-1]) {
            cur = i-1;
            next = i+1;
            ans = max(ans, longest[i-1]+1);
        }

        if (cur == -1) {
            ans = max(longest[i], ans);
        } else  {
            if (next == n) {
                ans = max(ans, longest[i]+1);
            } else if (arr[next] > arr[cur]+1) {
                ans = max(longest[i]+longest[cur], ans);
            } else {
                ans = max(ans, longest[i]+1);
            }
        }
    }

    cout << ans << endl;
}