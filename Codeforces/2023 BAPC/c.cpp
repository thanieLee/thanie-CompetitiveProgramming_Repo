#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


pair<int, int> addPair(pair<int, int> x, pair<int, int> y) {
    return {x.first+y.first, x.second+y.second};
}



int main(){
    int n; cin >> n;
    int cnt = 1;
    
    vector<map<string, int>> dir(1);
    vector<vector<int>> adj(1, vector<int>());
    vector<int> parents(cnt, 0);
    vector<int> nodeCount(cnt, 1);
    for (int i = 0; i < n; i++){
        string path; cin >> path;
        path += '/';
        vector<int> pos;
        for (int j = 0; j < path.size(); j++){
            if (path[j] == '/') {
                pos.push_back(j);
            }
        }


        int cur = 0;
        for (int j = 1; j < pos.size(); j++){
            int curPos = pos[j];
            if (dir[cur].find(path.substr(pos[j-1]+1, curPos-(pos[j-1]+1))) == dir[cur].end()) {
                dir.push_back(map<string, int>());
                adj.push_back(vector<int>());
                parents.push_back(0);
                dir[cur][path.substr(pos[j-1]+1, curPos-(pos[j-1]+1))] = cnt;
                adj[cur].push_back(cnt);
                nodeCount.push_back(1);
                parents[cnt] = cur;
                cur = cnt;
                cnt++;
            } else {
                if (j == pos.size()-1) {
                    dir.push_back(map<string, int>());
                    adj.push_back(vector<int>());
                    parents.push_back(0);
                    dir[cur][path.substr(pos[j-1]+1, curPos-(pos[j-1]+1))] = cnt;
                    adj[cur].push_back(cnt);
                    nodeCount.push_back(1);
                    parents[cnt] = cur;
                    cur = cnt;
                cnt++;
                }
                cur = dir[cur][path.substr(pos[j-1]+1, curPos-(pos[j-1]+1))];
            }
        }


    }

    vector<bool> isLeaf(cnt, false);
    deque<int> order, q;

    vector<pair<int, int>> dp(cnt, {0, 0});

    for (int i = 0; i < cnt; i++) {
        if (adj[i].size() == 0) {
            isLeaf[i] = true;
        }
    }
    int leafCnt = 0;
    for (int i = 0; i < cnt; i++){
        if (isLeaf[i]) {
            dp[i] = {0, nodeCount[i]};
            leafCnt++;
        }
    }


    q.push_back(0);
    while(!q.empty()){
        int cur = q.front();
        order.push_front(cur);
        q.pop_front();
        for (int v : adj[cur]) {
            q.push_back(v);
        }
    }

    deque<int> orderCopy = order;
    
    while (orderCopy.size() > 1) {
        int cur = orderCopy.front();
        orderCopy.pop_front();

        dp[parents[cur]] = addPair(dp[parents[cur]], {dp[cur].first+dp[cur].second, dp[cur].second});
    }
    
    vector<int> addon(cnt, 0);
    q.push_back(0);
    addon[0] = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front();
        for (int v : adj[cur]) {
            addon[v] = addon[cur] + (leafCnt-dp[v].second) + (dp[cur].first-dp[v].first-dp[v].second);
            q.push_back(v); 
        }
    }
    int ans = 1000000000;
    for (int i = 0; i < cnt; i++){
        if (i != 0 and !isLeaf[i]) {
            ans = min(ans, dp[i].first+addon[i]);
        } else if (!isLeaf[i]) {
            ans = min(ans, dp[i].first);
        }
    }
    cout << ans << endl;
}