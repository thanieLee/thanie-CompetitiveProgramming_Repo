#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    int cnt = 0;

    vector<int> arr;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        arr.push_back(x);

        cnt += x;
    }

    sort(arr.begin(), arr.end());

    if (cnt % 10 != 0){
        cout << cnt << endl;
        return 0;
    } else {
        int idx = 0;

        while (idx < n and arr[idx]%10 == 0) {
            idx++;
            if (idx == n) break;
        }

        if (idx == n) {
            cout << 0 << endl;
        } else {
            cout << cnt - arr[idx] << endl;
        }
    }
}