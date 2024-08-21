#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<int> arr;
    multiset<int> left, right;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr.push_back(x);
        right.insert(x);
    }

    int m = 0;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        left.insert(arr[i]);
        if (*left.rbegin() == arr[i] and *right.begin() == arr[i]) {
            m++;
            ans.push_back(arr[i]);
        }
        right.erase(right.find(arr[i]));
    }

    cout << m << " ";
    for (int i = 0; i < min((int)ans.size(), 100); i++) {
        cout << ans[i] << " ";
    }
}