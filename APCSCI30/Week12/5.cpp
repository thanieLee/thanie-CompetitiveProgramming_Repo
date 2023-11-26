#include <bits/stdc++.h>
using namespace std;

int nodeCount = 100001;
vector<int> disc(nodeCount, -1), low(nodeCount, -1);
vector<vector<int>> adj(nodeCount, vector<int>());
set<pair<int, int>> edges;
int timer = 0;
int bridgeCount = 0;
stack<pair<int, int>> bccStack;
vector<vector<pair<int, int>>> bccs = {{}};
vector<int> isArt(nodeCount, false);
int artCount = 0;
int sccCount = 0;
vector<int> sccParent(nodeCount, -1);
vector<vector<int>> BCTreeAdj(nodeCount, vector<int>());
vector<int> artToNode(nodeCount, -1);

pair<int, int> edge(int i, int j){
    return {min(i, j), max(i, j)};
}


void get_bcc(pair<int, int> e){
    sccCount++;
    vector<pair<int, int>> bcc;
    pair<int, int> E;
    do {
        E = bccStack.top();
        sccParent[E.first] = sccCount;
        sccParent[E.second] = sccCount;
        bccStack.pop();
        bcc.push_back(E);
    } while (E != e);

    bccs.push_back(bcc);
}

void dfs(int i, int p){
    disc[i] = low[i] = timer++;

    int children = 0;
    bool hasLowChild = false;
    for (int j : adj[i]){
        if (disc[j] == -1){
            bccStack.push(edge(i, j));
            dfs(j, i);

            low[i] = min(low[i], low[j]);
            children++;

            if (low[j] >= disc[i]){
                hasLowChild = true;
                get_bcc(edge(i, j));
            }
        } else if(j != p){
            low[i] = min(low[i], disc[j]);
        }
    }

    if ((p == -1 and children >= 2) or (p != -1 and hasLowChild)){
        isArt[i] = true;
        artCount++;
    }
}

void actPointsAndBcc(int &n){
    for (int i = 1; i <= n; i++){
        if (disc[i] == -1){
            dfs(i, -1);
        }
    }
}

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

int main(){
    int n, m, q; cin >> n >> m >> q;
    for (int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    actPointsAndBcc(n);

    graph g(bccs.size()+1+artCount);
    int sccTotal = bccs.size()+1;
    int sccCount = 0;
    int artCnt = 0;
    for (auto bcc : bccs){
        for (pair<int, int> edge : bcc){

            if (isArt[edge.first]){
                if (artToNode[edge.first] == -1){
                    artToNode[edge.first] = artCnt++;
                }
    
                g.adj[sccCount].push_back(sccTotal+artToNode[edge.first]);
                g.adj[sccTotal+artToNode[edge.first]].push_back(sccCount);
            }

            if (isArt[edge.second]){
                if (artToNode[edge.second] == -1){
                    artToNode[edge.second] = artCnt++;
                }
                g.adj[sccCount].push_back(sccTotal+artToNode[edge.second]);
                g.adj[sccTotal+artToNode[edge.second]].push_back(sccCount);
            }

            sccParent[edge.first] = sccCount;
            sccParent[edge.second] = sccCount;
        }
        sccCount++;
    }
    //cout << sccCount << " " << bccs.size() << endl;
    g.dfs(1, 1, 0);

    for (int i = 0; i < q; i++){
        int a, b, c; cin >> a >> b >> c;
        int aParent = sccParent[a];
        int bParent = sccParent[b];
        //cout << a << " " << b << " " << c << " ";
        

        if (c == a or c == b) {
            cout << "NO" << endl;
            continue;
        }
        if (!isArt[c]) {
            cout << "YES" << endl;
            continue;
        }
        if (isArt[a]){
            aParent = sccTotal+artToNode[a];
        }

        if (isArt[b]){
            bParent = sccTotal+artToNode[b];
        }

        int cPoint = sccTotal+artToNode[c];
        //cout << aParent << " " << bParent << " " << cPoint << endl;
        //cout << g.lca(aParent, cPoint) << " " << g.lca(cPoint, bParent) << endl;

        int ABLcaDepth = g.dep[g.lca(aParent, bParent)];
        if ((g.lca(aParent, cPoint) == cPoint and ABLcaDepth <= g.dep[cPoint]) or (g.lca(bParent, cPoint) == cPoint and ABLcaDepth <= g.dep[cPoint])){
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }

}