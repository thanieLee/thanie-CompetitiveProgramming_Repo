#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

ll firstEdge = -1;
void dfs(ll u, ll p, ll& dfsCnt, vector<ll>&edgeArr, vector<bool> &vis, vector<set<pll>> &adj) {
    vis[u] = true;
    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
        edgeArr[it->second] = dfsCnt;
        if (!vis[it->first]) {
            dfs(it->first, u, dfsCnt, edgeArr, vis, adj);
            if (firstEdge == -1) {
                firstEdge = it->second;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
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
        string s; cin >> s;
        ll a, b; cin >> a >> b; a--; b--;
        if (a > b) swap(a, b);
        swaps.push_back({a, b});
        adj[a].insert({b, i});
        adj[b].insert({a, i});
    }
    
    for (int i = 0; i < n; i++){
        if (adj[i].size() < 1) continue; 
        auto last = adj[i].end();
        last--;
        //cout << i << endl;
        for (auto it = adj[i].begin(); it != last; it++) {
            auto next = it;
            next++;
            //cout << it->first << " " << next->first << " " << (it->first == next->first) << endl;
            if (it->first == next->first) {
                cout << "YES" << '\n';
                vector<bool> perm1(c, false), perm2(c, false);
                cout << it->second+1 << " " << next->second+1 << " ";
                perm1[it->second] = true;
                perm1[next->second] = true;
                for (int i = 0; i < c; i++) {
                    if (!perm1[i]) cout << i+1 << " ";
                }
                cout << endl;

                cout << next->second+1 << " " << it->second+1 << " ";
                perm2[it->second] = true;
                perm2[next->second] = true;
                for (int i = 0; i < c; i++) {
                    if (!perm2[i]) cout << i+1 << " ";
                }
                cout << endl;
                return 0;
            }
        }
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
        //cout << edgeArr[i] <<  " ";
        if (edgeArr[i] > 0) {
            valid = false;
        } else if (edgeArr[i] < 0) {
            cout << "mia" << endl;
            return 0;
        }
    }
    if (firstEdge == -1) {
        cout << "mama" << endl;
        return 0;
    }
    //cout << '\n';
    
    if (!valid) {
        for (int i = 0; i < c; i++) {
            if (edgeArr[i] != edgeArr[firstEdge]) {
                cout << "YES" << '\n';
                vector<bool> perm1(c, false), perm2(c, false);
                for (int j = 0; j < c; j++) {
                    if (edgeArr[j] == edgeArr[i]) {
                        cout << j+1 << " ";
                        perm1[j] = true;
                    }
                }

                for (int j = 0; j < c; j++) {
                    if (edgeArr[j] == edgeArr[firstEdge]) {
                        cout << j+1 << " ";
                        perm1[j] = true;
                    }
                }

                for (int j = 0; j < c; j++) {
                    if (!perm1[j]) {
                        cout << j+1 << " ";
                    }
                }
                cout << '\n';

                for (int j = 0; j < c; j++) {
                    if (edgeArr[j] == edgeArr[firstEdge]) {
                        cout << j+1 << " ";
                        perm2[j] = true;
                    }
                }

                for (int j = 0; j < c; j++) {
                    if (edgeArr[j] == edgeArr[i]) {
                        cout << j+1 << " ";
                        perm2[j] = true;
                    }
                }

                for (int j = 0; j < c; j++) {
                    if (!perm2[j]) {
                        cout << j+1 << " ";
                    }
                }
                cout << '\n';
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
    
    if (tempCnt == c-1) {
        for (int i = 0; i < c; i++) {
            auto sw = swaps[i];
            bool check1 = adj[maxIdx].lower_bound({sw.first, -1})->first == sw.first;
            bool check2 = adj[maxIdx].lower_bound({sw.second, -1})->first == sw.second;
            if (sw.first != maxIdx and sw.second != maxIdx and check1 and check2) {
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
        if (s1i == -1 or s2i == -1 or outlieridx == -1) {
            goto hell;
            return 0;
        }
        cout << "YES" << '\n';
        vector<ll> order = {s1i, s2i, outlieridx};
        vector<bool> perm1(c, false), perm2(c, false);
        sort(order.begin(), order.end());
        ll n1i = order[0];
        ll n2i = order[2];
        cout << order[0]+1 << " " << order[1]+1 << " " << order[2]+1 << " ";
        perm1[order[0]] = true;
        perm1[order[1]] = true;
        perm1[order[2]] = true;
        for (int i = 0; i < c; i++) {
            if (!perm1[i]) {
                cout << i+1 << " ";
            }
        }
        cout << '\n';

        cout << order[2]+1 << " " << order[1]+1 << " " << order[0]+1 << " ";
        perm2[order[0]] = true;
        perm2[order[1]] = true;
        perm2[order[2]] = true;
        for (int i = 0; i < c; i++) {
            if (!perm2[i]) {
                cout << i+1 << " ";
            }
        }
        cout << '\n';

        return 0;
    } else if (tempCnt < c-1) {
        hell:
        ll tempSize = c;
        ll curIdx = -1;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() < tempSize and adj[i].size() > 0) {
                tempSize = adj[i].size();
                curIdx = i;
            }
        }
        //cout << tempSize << " " << curIdx << endl;
        ll curNext = adj[curIdx].begin()->first;
        //cout << curIdx << " " << curNext << endl;
        for (int i = 0; i < c; i++) {
            if (swaps[i].first != curIdx and swaps[i].first != curNext and swaps[i].second != curIdx  and swaps[i].second != curNext) {
                vector<bool> perm1(c, false), perm2(c, false);
                cout << "YES" << endl;
                cout << adj[curIdx].begin()->second+1 << " " << i+1 << " ";
                perm1[adj[curIdx].begin()->second] = true;
                perm1[i] = true;
                for (int j = 0; j < c; j++) {
                    if (!perm1[j]) {
                        cout << j+1 << " ";
                    }
                }
                cout << endl;

                cout << i+1 << " " << adj[curIdx].begin()->second+1 << " ";
                perm2[adj[curIdx].begin()->second] = true;
                perm2[i] = true;
                for (int j = 0; j < c; j++) {
                    if (!perm2[j]) {
                        cout << j+1 << " ";
                    }
                }
                cout << endl;
                return 0;
            }
        }
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
        if (it->second.size() >= 3) {
            cout << "YES" << '\n';
            vector<bool> perm1(c, false), perm2(c, false);
            cout << it->second[0]+1 << " " << it->second[1]+1 << " " << it->second[2]+1 << " ";
            for (int i = 0; i < 3; i++) {
                perm1[it->second[i]] = true;
            }

            for (int i = 0; i < c; i++) {
                if (!perm1[i]) {
                    cout << i+1 << " ";
                }
            }
            cout << '\n';
            cout << it->second[0]+1 << " " << it->second[2]+1 << " " << it->second[1]+1 << " ";
            for (int i = 0; i < 3; i++) {
                perm2[it->second[i]] = true;
            }

            for (int i = 0; i < c; i++) {
                if (!perm2[i]) {
                    cout << i+1 << " ";
                }
            }
            cout << '\n';
            return 0;
        } else if (it->second.size() >= 2 and maxVal == it->first) {
            cout << "YES" << '\n';
            vector<bool> perm1(c, false), perm2(c, false);
            vector<ll> cur = it->second;
            cout << cur[0]+1 << " " << cur[1]+1 << " ";
            for (int i = 0; i < 2; i++) {
                perm1[cur[i]] = true;
            }

            for (int i = 0; i < c; i++) {
                if (!perm1[i]) {
                    cout << i+1 << " ";
                }
            }
            cout << '\n';

            cout << cur[1]+1 << " " << cur[0]+1 << " ";
            for (int i = 0; i < 2; i++) {
                perm2[cur[i]] = true;
            }

            for (int i = 0; i < c; i++) {
                if (!perm2[i]) {
                    cout << i+1 << " ";
                }
            }
            cout << '\n';
            return 0;
        }
    }

    ll temp1 = -1;
    vector<ll> tempVec1;
    ll temp2 = -1;
    vector<ll> tempVec2;
    for (auto it = aCnt.begin(); it != aCnt.end(); it++) {
        if (temp1 == -1 and it->second.size() >= 2 and it->first != maxVal) {
            temp1 = it->first;
            tempVec1 = it->second;
        } else if (temp2 == -1 and it->second.size() >= 2 and it->first != temp1 and it->first != maxVal) {
            temp2 = it->first;
            tempVec2 = it->second;
        } else if (temp2 == -1 and it->second.size() >= 1 and it->first != temp1 and it->first == maxVal) {
            temp2 = it->first;
            tempVec2 = it->second;
        }
    }
    if (temp1 == -1 or temp2 == -1) {
        cout << "NO" << '\n';
        return 0;
    }

    if (temp2 == maxVal) {
        cout << "YES" << '\n';
        vector<bool> perm1(c, false), perm2(c, false);
        cout << tempVec1[0]+1 << " " << tempVec2[0]+1 << " " << tempVec1[1]+1 << " ";
        perm1[tempVec1[0]] = true;
        perm1[tempVec2[0]] = true;
        perm1[tempVec1[1]] = true;
        for (int i = 0; i < c; i++) {
            if (!perm1[i]) {
                cout << i+1 << " ";
            }
        }
        cout << '\n';

        cout << tempVec1[1]+1 << " " << tempVec2[0]+1 << " " << tempVec1[0]+1 << " ";
        perm2[tempVec1[0]] = true;
        perm2[tempVec2[0]] = true;
        perm2[tempVec1[1]] = true;
        for (int i = 0; i < c; i++) {
            if (!perm2[i]) {
                cout << i+1 << " ";
            }
        }
        cout << '\n';

    } else {
        cout << "YES" << '\n';
        vector<bool> perm1(c, false), perm2(c, false);
        cout << tempVec1[0]+1  << " " <<  tempVec2[0]+1 << " " << tempVec1[1]+1 << " " << tempVec2[1]+1 << " ";
        perm1[tempVec2[0]] = true;
        perm1[tempVec1[0]] = true;
        perm1[tempVec2[1]] = true;
        perm1[tempVec1[1]] = true;
        for (int i = 0; i < c; i++) {
            if (!perm1[i]) {
                cout << i+1 << " ";
            }
        }
        cout << '\n';

        cout << tempVec1[0]+1  << " " << tempVec2[1]+1 << " " << tempVec1[1]+1 << " " << tempVec2[0]+1 << " ";
        perm2[tempVec2[0]] = true;
        perm2[tempVec1[0]] = true;
        perm2[tempVec2[1]] = true;
        perm2[tempVec1[1]] = true;
        for (int i = 0; i < c; i++) {
            if (!perm2[i]) {
                cout << i+1 << " ";
            }
        }
        cout << '\n';
    }
}