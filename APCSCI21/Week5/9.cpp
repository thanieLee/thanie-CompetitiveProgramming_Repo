#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int nodeCnt = 0, freeCnt = 0;
int n, m, k;
void dfs(int u, vector<bool> &vis, vector<vector<int>>& adj){
    if (vis[u] or nodeCnt >= freeCnt-k) return;
    vis[u] = true;
    nodeCnt++;

    for (int v : adj[u]){
        dfs(v, vis, adj);
    }
}

int pointToNode(int i, int j){
    return i*m + j;
}

pair<int, int> nodeToPoint(int node){
    return {(int)floor(node/n), node%n};
}


int main(){
    cin >> n >> m >> k;
    pair<int, int> curNode;
    vector<vector<bool>> graph(n, vector<bool>(m, true));
    vector<vector<int>> adj(n*m, vector<int>());
    vector<pair<int, int>> delta = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    for (int i = 0; i < n; i++){
        string s; cin >> s;
        for (int j = 0; j < m; j++){
            if (s[j] == '#'){
                graph[i][j] = false;
            } else {
                freeCnt++;
                curNode = {i, j};
            }
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (graph[i][j]) {
                for (int k = 0; k < 4; k++){
                    int newx = i + delta[k].first;
                    int newy = j + delta[k].second;
                    if (!(0 <= newx and newx < n) or !(0 <= newy and newy < m)) continue;
                    if (graph[newx][newy]) {
                        adj[pointToNode(i, j)].push_back(pointToNode(newx, newy));
                    }
                }
            }
        }
    }

    vector<bool> vis(n*m, false);
    dfs(pointToNode(curNode.first, curNode.second), vis, adj);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (vis[pointToNode(i, j)]) {
                cout << ".";
            } else if (graph[i][j]) {
                cout << "X";
            } else {
                cout << "#";
            }
        }
        cout << endl;
    }

}