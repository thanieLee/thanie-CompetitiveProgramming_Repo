#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


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

int prevVal(int x){
    string xs = to_string(x);
    int val = x;
    for (char c : xs){
        val -= c-'0';
    }
    return val;
}

int main(){
    int n, k; cin >> n >> k;
    vector<int> f;
    for (int i = 0; i < n; i++){
        int fi; cin >> fi;
        f.push_back(fi);
    }
	sort(f.begin(), f.end());
    graph g(1e6+1);
    vector<int> val(1e6+1, 0);
    for (int i = 1; i<=1e6; i++){
        g.adj[prevVal(i)].push_back(i);
        val[i] = prevVal(i);
    }
    g.dfs(0, 0, 0);

    for (int i = 1; i <= 1e6; i++){
        for (int j = 1; j < 100; j++){
            int curi = i, curj = i+j;
            if ((curi%9) or (curj%9)) continue;
            while (val[curj] > curi) curj = val[curj];
            bool isJ = true;
            while (curi != curj) {
                 if (!isJ and curj > curi) {
                    cout << "oops i" << endl;
                    cout << i << ' ' << i+j << " " << curi << " " << curj << " " << isJ << endl;
                    return 0;
                } else if (isJ and curj > curi) {
                    curj = val[curj];
                } else if (!isJ and curi > curj) {
                    curi = val[curi];
                }
                isJ = not isJ;
            }
        }
    }
    

}