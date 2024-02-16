#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++){
        int ai; cin >> ai;
        a.push_back(ai);
    }


    ll cost = 10000000000000;
    for (int i = -1000; i < 1001; i++){
        ll tempCost = 0;
        for (int j = 0; j < n; j++){
            tempCost += pow(a[j]-i, 2);
        }
        cost = min(cost, tempCost);
    }

    cout << cost << endl;
}