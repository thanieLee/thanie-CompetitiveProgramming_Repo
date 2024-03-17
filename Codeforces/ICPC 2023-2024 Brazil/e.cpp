#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> pii;

vector<int> f;

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

    int dist(int u, int v){
        return (dep[u]+dep[v])-2*(dep[lca(u, v)]);
    }
};

int delta(int x){
    string xs = to_string(x);
    int val = 0;
    for (char c : xs){
        val += c-'0';
    }
    return val;
}


int main(){
    int n, k; cin >> n >> k;
    
	set<int> uniq;
	f.resize(n);
    for (int i = 0; i < n; i++) {
		cin >> f[i];
		uniq.insert(f[i]);
	}
	
	sort(f.begin(), f.end(), greater());

	graph g(1e6+1);
    for (int i = 1; i<=1e6; i++){
        g.adj[i - delta(i)].push_back(i);
    }
    g.dfs(0, 0, 0);
	
	auto check = [&] (int val) -> tuple<int,int,bool> {
		bool found = false;
		int lo = 0, hi = 0;

		for (int i : f) {
			lo += g.dist(i, val);
			hi += g.dist(i, val-1);
			// int dst = g.dist(i, val);
			// if (!found)
			// 	lo += dst;
			// hi += dst;

			if (g.is_anc(i, val))
				found = true;
		}

		return {lo, max(lo, hi-1), found};
	};
	
    vector<int> arr1, arr2;
	for (int i = 0; i <= *(uniq.rbegin()); i += 9)
		arr1.push_back(i);
	for (int i : uniq)
		arr2.push_back(i);

 



} 	