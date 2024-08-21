#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

int main(){
    int n, k; cin >> n >> k;
    vector<pii> intervals;

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        intervals.push_back({a, b});
    }
    sort(intervals.begin(), intervals.end());

    
}