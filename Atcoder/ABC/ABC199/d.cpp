#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<int> colors;
int n;
vector<vector<bool>> adj;
vector<bool> vis, tempVis;
vector<vector<bool>> transition;
ll ans = 0;
ll cnt = 1;

void dfs(int u, int p, int colorCnt) {
    //cout << u << " " << p << " " << colorCnt << endl;
    // cout << "colors: ";
    // for (int i = 0; i < n; i++) {
    //     cout << colors[i] << " ";
    // }
    // cout << endl;
    bool canContinue = false;
    vis[u] = true;

    vector<bool> canColor = {true, true, true};

    for (int v = 0; v < n; v++) {
        if (!adj[u][v]) continue;
        if (colors[v] != -1) {
            canColor[colors[v]] = false;
            if (v != p) {
                transition[u][v] = true;
                transition[v][u] = true;
            }
        }
    }


    for (int v = 0; v < n; v++) {
        if (!adj[u][v]) continue;
        if (colors[v] == -1) canContinue = true;
    }

    if (!canContinue) {
        for (int i = 0; i < 3; i++) {
            if (canColor[i]) {
                colors[u] = i;
                ans++;
                colors[u] = -1;
            }
        }
        return;
    }

    for (int i = 0; i < 3; i++) {
        if (!canColor[i]) continue;
        colors[u] = i;
        for (int v = 0; v < n; v++) {
            if (!adj[u][v] or transition[u][v]) continue;
            if (colors[v] != -1) continue;
            dfs(v, u, colorCnt+1);
        }
        colors[u] = -1;
    }
}

int main(){
    int m; cin >> n >> m;
    vis.resize(n, false);
    tempVis.resize(n, false);
    adj.resize(n, vector<bool>(n, false));
    colors.resize(n, -1);
    transition.resize(n, vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a][b] = true;
        adj[b][a] = true;
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            for (int j = 0; j < n; j++) tempVis[j] = false;
            ans = 0;
            dfs(i, -1, 0);
            cnt *= ans;
        } 
    }
    cout << cnt << endl;
}