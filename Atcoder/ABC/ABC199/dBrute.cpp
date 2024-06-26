#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


vector<vector<int>> possible;
vector<vector<bool>> adj;
vector<vector<int>> adjList;
int n;
vector<int> scc;
vector<bool> vis;
vector<int> visOrder, orderVis;
vector<int> colors;
int timer = 0;
ll curAns = 0;
void gen(int &cur_scc) {
    if (colors.size() == n) {
        curAns++;
        return;
    }
    if (scc[visOrder[colors.size()]] != cur_scc) {
        colors.push_back(-1);
        gen(cur_scc);
        colors.pop_back();
        return;
    }
    for (int i = 0; i < 3; i++) {
        bool can = true;
        for (int j : adjList[visOrder[colors.size()]]) {
            if (orderVis[j] >= colors.size()) continue;
            if (colors[orderVis[j]] == i) can = false;
        }
        if (!can) continue;
        colors.push_back(i);
        gen(cur_scc);
        colors.pop_back();
    }
}

void dfs(int u, int p, int &comp_cnt) {
    vis[u] = true;
    visOrder.push_back(u);
    scc[u] = comp_cnt;
    for (int v : adjList[u]) {
        if (!vis[v]) dfs(v, u, comp_cnt);
    }
}

int main(){
    int m; cin >> n >> m;
    adj.resize(n, vector<bool>(n, false));
    scc.resize(n, -1);
    vis.resize(n, false);
    adjList.resize(n, vector<int>());
    orderVis.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a][b] = true;
        adj[b][a] = true;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, -1, timer);
            timer++;
        }
    }

    for (int i = 0; i < n; i++) {
        orderVis[visOrder[i]] = i;
    }

    vector<int> temp;
    ll ans = 1;
    for (int i = 0; i < timer; i++) {
        gen(i);
        ans *= curAns;
        curAns = 0;
    }
    cout << ans << endl;

}