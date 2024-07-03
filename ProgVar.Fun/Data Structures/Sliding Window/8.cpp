#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, m; cin >> n >> m;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
    }
    set<int> all;
    for (int i = 0; i <= n; i++) {
        all.insert(i);
    }

    multiset<int> current;
    for (int i = 0; i < m; i++) {
        current.insert(a[i]);
        all.erase(a[i]);
    }

    int ans = *all.begin();

    for (int i = m; i < n; i++) {
        int prev = a[i-m];
        current.erase(current.find(prev));
        if (current.find(prev) == current.end()) {
            all.insert(prev);
        }

        current.insert(a[i]);
        all.erase(a[i]);

        ans = min(ans, *all.begin());
    }

    cout << ans << endl;
}