#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

bool cmp(pair<int, int> &x, pair<int, int> &y){
    return x.second < y.second;
}

int main(){
    int n; cin >> n;
    vector<pair<int, int>> a;

    for (int i = 0; i < n; i++){
        int ai; cin >> ai;
        a.push_back({i+1, ai});
    }

    sort(a.begin(), a.end(), cmp);

    for (int i = 0; i < n; i++){
        cout << a[i].first << " ";
    }
    cout << endl;
}