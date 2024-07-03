#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

int main(){
    int n, m; cin >> n >> m;
    vector<pii> conditions;
    for (int i = 0; i < m; i++) {
        int ai, bi; cin >> ai >> bi; ai--; bi--;
        conditions.push_back({ai, bi});
    }
    int k; cin >> k;
    vector<int> c, d;
    for (int i = 0; i < k; i++) {
        int ci, di; cin >> ci >> di; ci--; di--;
        c.push_back(ci);
        d.push_back(di);
    }
    

    int ans = 0;
    for (int msk = 0; msk < (1<<k); msk++) {
        vector<bool> balls(n, false);
        for (int i = 0; i < k; i++) {
            if (!(msk & (1<<i))) {
                balls[c[i]] = true;
            } else {
                balls[d[i]] = true;
            }
        }
        int cnt = 0;
        for (pii cond : conditions) {
            if (balls[cond.first] and balls[cond.second]) cnt++;
        }
        ans = max(cnt, ans);
    }
    cout << ans << endl;
}