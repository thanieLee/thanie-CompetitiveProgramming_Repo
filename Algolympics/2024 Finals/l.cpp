#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

ll firstEdge = -1;
void dfs(ll u, ll p, ll& dfsCnt, vector<ll>&edgeArr, vector<bool> &vis, vector<set<pll>> &adj) {
    vis[u] = true;
    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
        if (!vis[it->first]) {
            dfs(it->first, u, dfsCnt, edgeArr, vis, adj);
            edgeArr[it->second] = dfsCnt;
            if (firstEdge == -1) {
                firstEdge = it->second;
            }
        }
    }
}



int main(){
    int n; cin >> n;
    vector<ll> a;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        a.push_back(x);
    }
    int c; cin >> c;
    vector<pll> swaps;
    vector<set<pll>> adj(n, set<pll>());
    for (int i = 0; i < c; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        if (a > b) swap(a, b);
        swaps.push_back({a, b});
        pll search = {b, -1};
        pll check = *lower_bound(adj[a].begin(), adj[a].end(), search);
        if (check.first == b) {
            cout << "YES" << endl;
            vector<ll> ans;
            for (int i = 1; i <= c; i++) {
                ans.push_back(i);
                cout << i << " ";
            }
            cout << endl;
            ll temp = ans[check.second];
            ans[check.second] = i+1;
            ans[i] = temp;
            for (int i = 0; i < c; i++) {
                cout << ans[i] << " ";
            }
            cout << endl;
            return 0;
        }
        adj[a].insert({b, i});
        adj[b].insert({a, i});
    } 

    vector<ll> edgeArr(c, -1);
    ll dfsCnt = 0;
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, -1, dfsCnt, edgeArr, vis, adj);
            dfsCnt++;
        }
    }

    bool valid = true;
    for (int i = 0; i < c; i++) {
        if (edgeArr[i] > 0) {
            valid = false;
        }
    }

    if (!valid) {
        for (int i = 0; i < c; i++) {
            if (edgeArr[i] != edgeArr[firstEdge]) {
                cout << "YES" << endl;
                vector<ll> ans;
                for (int i = 1; i <= c; i++) {
                    ans.push_back(i);
                    cout << i << " ";
                }
                cout << endl;
                ll temp = ans[firstEdge];
                ans[firstEdge] = i+1;
                ans[i] = temp;
                for (int i = 0; i < c; i++) {
                    cout << ans[i] << " ";
                }
                cout << endl;
                return 0;
            }
        }
    }

    vector<ll> swapCnt(n, 0);

    for (auto sw : swaps) {
        swapCnt[sw.first]++;
        swapCnt[sw.second]++;
    }

    int tempCnt = 0;
    ll maxIdx = -1;
    for (int i = 0; i < n; i++) {
        if (tempCnt < swapCnt[i]) {
            tempCnt = swapCnt[i];
            maxIdx = i;
        }
    }

    pll outlier = {-1, -1};
    ll outlieridx = -1;
    if (tempCnt < c) {

        for (int i = 0; i < c; i++) {
            auto sw = swaps[i];
            if (sw.first != maxIdx and sw.second != maxIdx) {
                outlier = sw;
                outlieridx = i;
            }
        }
        
        pll s1 = {min(maxIdx, outlier.first), max(maxIdx, outlier.first)};
        pll s2 = {min(maxIdx, outlier.second), max(maxIdx, outlier.second)};
        ll s1i = -1;
        ll s2i = -1;
        for (int i = 0; i < c; i++) {
            pll cur = swaps[i];
            if (cur == s1) {
                s1i = i;
            } else if (cur == s2) {
                s2i = i;
            }
        }

        vector<ll> order = {s1i, s2i, outlieridx};
        sort(order.begin(), order.end());
        ll n1i = order[0];
        ll n2i = order[2];
        cout << "YES" << endl;
        vector<ll> ans;
        for (int i = 1; i <= c; i++) {
            ans.push_back(i);
            cout << i << " ";
        }
        cout << endl;
        ll temp = ans[n1i];
        ans[n1i] = n2i+1;
        ans[n2i] = temp;
        for (int i = 0; i < c; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        return 0;
    }

    map<ll, vector<ll>> aCnt;
    for (int i = 0; i < c; i++) {
        ll cur = -1;
        auto curSw = swaps[i];
        if (curSw.first == maxIdx) {
            cur = a[curSw.second];
        } else {
            cur = a[curSw.first];
        }

        if (aCnt.find(cur) == aCnt.end()) {
            aCnt[cur] = {i};
        } else {
            aCnt[cur].push_back(i);
        }
    }

    ll maxVal = a[maxIdx];
    for (auto it = aCnt.begin(); it != aCnt.end(); it++) {
        if (it->second.size() == 3) {
            ll s = it->second[0], m = it->second[1], e = it->second[2];
            vector<ll> ans(n);
            for (int i = 1; i <= c; i++) {
                ans[i-1] = i;
                cout << i << " ";
            }
            cout << endl;
            ll curIdx = s+1;
            for (int i = m+1; i <= e; i++) {
                ans[curIdx] = i+1;
                curIdx++;
            }
            for (int i = s+1; i <= m; i++) {
                ans[curIdx] = i+1;
                curIdx++;
            }

            for (int i = 0; i < c; i++) {
                cout << ans[i] << " ";
            }
            cout << endl;
        } else if (it->second.size() == 2 and maxVal == it->first) {
            ll s = -1, m = it->second[0], e = it->second[1];
            vector<ll> ans(n);
            for (int i = 1; i <= c; i++) {
                ans[i-1] = i;
                cout << i << " ";
            }
            cout << endl;
            ll curIdx = s+1;
            for (int i = m+1; i <= e; i++) {
                ans[curIdx] = i+1;
                curIdx++;
            }
            for (int i = s+1; i <= m; i++) {
                ans[curIdx] = i+1;
                curIdx++;
            }

            for (int i = 0; i < c; i++) {
                cout << ans[i] << " ";
            }
            cout << endl;
        }
    }



}

