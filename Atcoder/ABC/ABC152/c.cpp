#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) (int)(x.size())

int main(){
    int n; cin >> n;
    set<int> perm;
    int ans = 0;
    for (int i = 0; i < n; i++){
        int ai; cin >> ai;
        perm.insert(ai);
        if (*perm.begin() == ai) ans++;
    }
    cout << ans << endl;
}