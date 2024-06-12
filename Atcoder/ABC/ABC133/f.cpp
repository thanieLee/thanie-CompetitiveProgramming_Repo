#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


struct color_graph {
	int n, l;
	vector<vector<int>> adj, par;
	vector<int> dep;

	color_graph(int n) : n(n) {
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

struct main_graph {
	int n, l;
	vector<vector<int>> adj, par;
	vector<int> dep;
    vector<color_graph> color_graphs;
    vector<bool> color_visited;
    vector<int> colors;

	main_graph(int n) : n(n) {
		l = ceil(log2(n));
		dep.resize(n);
		adj.resize(n, vector<int>());
		par.resize(n, vector<int>(l+1));
        colors.resize(n);
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

int main() {
    int n, q; cin >> n >> q;
    
}