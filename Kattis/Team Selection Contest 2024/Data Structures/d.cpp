#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, m; cin >> n >> m;
    vector<int> a, a_rev;
    int cum = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
        a_rev.push_back(ai);
        cum += ai;
    }

    reverse(a_rev.begin(), a_rev.end());

    for (int j = 0; j < m; j++) {
        out:
            if (j >= m) break;
        int query; cin >> query;
        if (query == cum) {
            cout << "Yes" << endl;
            continue;  
        }

        set<int> possible;
        possible.insert(0);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += a_rev[i];
            possible.insert(cnt);
        }

        if (possible.find(query) != possible.end()) {
            cout << "Yes" << endl;
            continue; 
        }

        int cur = 0;
        for (int i = 0; i < n; i++) {
            cur += a[i];
            possible.erase(possible.find(cnt));
            cnt -= a[i];
            if (possible.find(query-cur) != possible.end()) {
                cout << "Yes " << endl;
                j++;
                goto out;
            }
        }

        cout << "No" << endl;
    }
}