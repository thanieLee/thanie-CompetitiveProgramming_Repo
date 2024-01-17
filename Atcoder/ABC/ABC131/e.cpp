#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, k; cin >> n >> k;
    int ma = ((n-1) * (n-2))/2;
    if (n == 2 and k == 0) {
        cout << 1 << endl;
        cout << 1 << " " << 2 << endl;
        return 0;
    }

    if (n == 3 and k == 0) {
        cout << 3 << endl;
        cout << 1 << " " << 2 << endl;
        cout << 2 << " " << 3 << endl;
        cout << 1 << " " << 3 << endl;
        return 0;
    }

    if (k > ma) {
        cout << -1 << endl;
        return 0;
    }

    
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; i++){
        edges.push_back({1, i});
    }

    for (int i = 2; i <= n; i++){
        for (int j = i+1; j <= n; j++){
            edges.push_back({i, j});
        }
    }

    cout << (ma - k) + n-1 << endl;
    for (int i = 0; i < (ma - k) + n-1; i++){
        cout << edges[i].first << " " << edges[i].second << endl;
    }
}