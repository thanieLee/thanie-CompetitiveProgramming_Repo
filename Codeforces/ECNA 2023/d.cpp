#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    vector<int> arr;
    for (int i = 0; i < 10; i++) {
        int x; cin >> x;
        arr.push_back(x);
    }

    int n, kwf; cin >> n >> kwf;
    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        cnt += arr[i]*arr[i+5];
    }

    cnt /= 5;
    cout << (cnt*n)/kwf << endl;
}