#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

pii solve(int dep, int step) {
    if (dep == 1) return {0, 0};
    int half = dep/2;
    if ((step / (half*half)) == 1) {
        return solve(half, step-half*half);
    } else if ((step/(half*half)) == 2) {
        pii next = solve(half, step-half*half*2);
        return {next.first, next.second+half};
    } else if ((step/(half*half)) == 0) {
        pii next = solve(half, step);
        return {half-next.second+half-1, half-next.first-1};
    } else {
        pii next = solve(half, step-half*half*3);
        return {next.second+half, next.first+half};
    }
}

int main(){
    int n, m; cin >> n >> m;
    pii ans = solve(n, m-1);
    cout << ans.second+1 << " " << n-ans.first << endl;
}