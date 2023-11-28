#include <bits/stdc++.h>
using namespace std;


int nodeCount = 15;
vector<int> disc(nodeCount, -1), low(nodeCount, -1);
vector<vector<int>> adj(nodeCount, vector<int>());
vector<vector<bool>> isBridge(nodeCount, vector<bool>(nodeCount, false));
vector<bool> isArt(nodeCount, false);
int timer = 0;

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
                isBridge[i][j] = true;
                isBridge[j][i] = true;
            }

            if (low[j] >= disc[i]){
                hasLowChild = true;
            }
        } else if (j != p){
            // this means (i, j) is a back edge

            low[i] = min(low[i], disc[j]);
        }
    }

    if ((p == -1 and children >= 2) or (p != -1 and hasLowChild)){
        isArt[i] = true;
    }
}

void addEdge(int i, int j){
    adj[i-1].push_back(j-1);
    adj[j-1].push_back(i-1);
}

int main(){

    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(4, 5);
    addEdge(5, 1);
    addEdge(2, 6);
    addEdge(6, 7);
    addEdge(1, 8);
    addEdge(8, 9);
    addEdge(8, 10);
    addEdge(10, 11);
    addEdge(11, 12);
    addEdge(11, 13);
    addEdge(13, 14);
    addEdge(8, 12);
    addEdge(8, 13);
    addEdge(10, 15);

    DFS(0, -1);

    for (int i = 0; i < nodeCount; i++){
        cout << disc[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < nodeCount; i++){
        cout << low[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < nodeCount; i++){
        cout << isArt[i] << " ";
    }
    cout << endl;


    return 0;
}