#include <bits/stdc++.h>
using namespace std;


int nodeCount = 100001;
vector<int> disc(nodeCount, -1), low(nodeCount, -1);
vector<vector<int>> adj(nodeCount, vector<int>());
set<pair<int, int>> edges;
int timer = 0;
int bridgeCount = 0;

void DFS(int i, int p){
    disc[i] = low[i] = timer++;

    int children = 0;
    bool hasLowChild = false;

    for (auto j : adj[i]) {
        if (disc[j] == -1){
            // this means (i, j) is a tree edge
            DFS(j, i);
            // update low[i] and other data
            low[i] = min(low[i], low[j]);
            children++;

            if (low[j] > disc[i]){
                bridgeCount++;
            }

            if (low[j] >= disc[i]){
                hasLowChild = true;
            }
        } else if (j != p){
            low[i] = min(low[i], disc[j]);
        }
    }
}

void DFS1(int i, int p){
    disc[i] = timer++;
    for (auto j : adj[i]) {
        //cout << disc[j] << endl;
        if (disc[j] == -1){
            cout << j+1 << " " << i+1 << endl;
            DFS1(j, i);
        } else if (j != p){
            if (edges.find({min(i, j), max(i, j)}) != edges.end()) continue; 
            cout << j+1 << " " << i+1 << endl;
            edges.insert({min(i, j), max(i, j)});
        }
    }
}

void addEdge(int i, int j){
    adj[i].push_back(j);
    adj[j].push_back(i);
}

int main(){
    int n, m; cin >> n >> m;

    for (int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        addEdge(a, b);
    }

    int pass = 0;
    for (int i = 0; i < n; i++){
        if (disc[i] == -1){
            pass++;
            DFS(i, -1);
        }
    }

    if (pass > 1 or bridgeCount > 0) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    timer = 0;
    for (int i = 0; i < n; i++){
        disc[i] = -1;
    }
    DFS1(0, -1);

    return 0;
}