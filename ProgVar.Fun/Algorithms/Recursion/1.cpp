#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

void solve(int n, int source, int aux, int dest) {
    if (n == 0) return;

    solve(n-1, source, dest, aux);
    cout << source << " " << dest << endl;
    solve(n-1, aux, source, dest);
}

int main(){
    int n; cin >> n;
    cout << (1<<n)-1 << endl;
    solve(n, 1, 2, 3);
}