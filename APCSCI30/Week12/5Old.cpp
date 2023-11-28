#include <bits/stdc++.h>
using namespace std;


int nodeCount = 100001;
vector<int> disc(nodeCount, -1), low(nodeCount, -1);
vector<vector<int>> adj(nodeCount, vector<int>());
vector<int> mainGraph(nodeCount, 0);
set<pair<int, int>> edges;
vector<bool> isArt(nodeCount, false);
int timer = 0;
int bridgeCount = 0;
vector<vector<int>> noBridge(nodeCount, vector<int>());
vector<int> sccParent(nodeCount);
vector<vector<int>> bridgeAdj(nodeCount, vector<int>());

struct graph {
	int n, l;
	vector<vector<int>> adj, par;
	vector<int> dep;

	graph(int n) : n(n) {
		l = ceil(log2(n));
		dep.resize(n);
		adj.resize(n, vector<int>());
		par.resize(n, vector<int>(l+1));
	}

	void dfs(int u, int p, int d) {
        cout << u << " " << p << " " << d << endl;
		dep[u] = d;
		par[u][0] = p;
		for (int i = 1; i <= l; i++)
			par[u][i] = par[par[u][i-1]][i-1];

		for (int v : adj[u]) {
			if (v != p)
				dfs(v, u, d+1);
		}
	}
	int ascend(int u, int k) {
		for (int i = 0; i <= l; i++)
			if (k & (1 << i))
				u = par[u][i];
		return u;
	}
	bool is_anc(int u, int v) {
		if (dep[u] < dep[v])
			swap(u, v);
		return ascend(u, dep[u]-dep[v]) == v;
	}
	int lca(int u, int v) {
		if (dep[u] > dep[v])
			u = ascend(u, dep[u]-dep[v]);
		if (dep[v] > dep[u])
			v = ascend(v, dep[v]-dep[u]);
		if (u == v)
			return u;

		for (int i = l; i >= 0; i--) {
			if (par[u][i] != par[v][i]) {
				u = par[u][i];
				v = par[v][i];
			}
		}
		return par[u][0];
	}
}; // Populate adjacency array then call dfs(root, root, 0)

graph g(nodeCount);

void DFS(int i, int p){
    disc[i] = low[i] = timer++;
   // cout << i << " " << p << " test" << endl;
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
                //cout << i << " " << j << endl;
                bridgeCount++;
            } else {
                noBridge[i].push_back(j);
                noBridge[j].push_back(i);
            }

            if (low[j] >= disc[i]){
                hasLowChild = true;
            }
        } else if (j != p){
            low[i] = min(low[i], disc[j]);
        }
    }

    if ((p == -1 and children >= 2) or (p != -1 and hasLowChild)){
        isArt[i] = true;
    }
}

void DFS2(int i, int &parent, vector<bool>& visited){
    if (visited[i]) return;
    visited[i] = true;
    sccParent[i] = parent;

    for (int cur : noBridge[i]){
        DFS2(cur, parent, visited);
    }

}

int main(){
    int n, m, q; cin >> n >> m >> q;
    for (int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int l = ceil(log2(n));
    DFS(1, -1);
    vector<bool> visited(nodeCount, false);
    for (int i = 1; i <= n; i++){
        DFS2(i, i, visited);
    }
    //cout << bridgeCount << endl;
    for (int i = 1; i <= n; i++){
        for (int v : adj[i]){
            if (sccParent[i] == sccParent[v]) continue;
            g.adj[sccParent[i]].push_back(sccParent[v]);
            g.adj[sccParent[v]].push_back(sccParent[i]);
        }
    }
    cout << "hehe" << endl;
    g.dfs(sccParent[1], sccParent[1], 0);
    cout << "hehe" << endl;
    for (int i = 0; i < q; i++){
        int a, b, c; cin >> a >> b >> c;
        int aParent = sccParent[a];
        int bParent = sccParent[b];
        int cParent = sccParent[c];
        //cout << aParent << " " << bParent << " " << cParent << endl;
        int lca1 = g.lca(aParent, cParent);
        int lca2 = g.lca(bParent, cParent);
        if (aParent == bParent or ((bParent == cParent or aParent == cParent) and !isArt[c])) {
            cout << "YES" << endl;
            continue;
        }
        if ((lca1 == aParent and lca2 == cParent) or (lca2 == bParent and lca1 == cParent) or (g.lca(aParent, bParent) == cParent)){
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }



}