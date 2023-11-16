#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<ll, ll> ii;
typedef pair<ll, pair<ll, ll>> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<pair<ii, ii>> viiii;

struct graph {
  ll n, *dist;
  vii *adj;

  graph(ll n) {
    this->n = n;
    adj = new vii[n];
    dist = new ll[n];
  }

  void add_edge(ll u, ll v, ll w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  void prim(viii &res, ll s, vector<bool> &vis) {
    res.clear();
    std::priority_queue<iii, viii, std::greater<iii>> pq;
    vis[s] = true;
    for (auto &[v, w] : adj[s])
        if (!vis[v]) pq.push({w, {s, v}});
    while (!pq.empty()) {
        auto edge = pq.top();    pq.pop();
        ll u = edge.second.second;
        if (vis[u]) continue;
        vis[u] = true;
        res.push_back(edge);

        for (auto &[v, w] : adj[u])
        if (!vis[v]){ pq.push({w, {u, v}});}}
  }
};

struct graph1 {
	int n, l;
	vector<vector<ii>> adj, par;
	vector<int> dep;

	graph1(int n) : n(n) {
		l = ceil(log2(n));
		dep.resize(n);
		adj.resize(n, vector<ii>());
		par.resize(n, vector<ii>(l+1));
	}

	void dfs(int u, int p, int d, ll w) {
		dep[u] = d;
		par[u][0] = {p, w};
		for (int i = 1; i <= l; i++){
            ll jump = par[par[u][i-1].first][i-1].first;
            ll weight = max(par[u][i-1].second, par[par[u][i-1].first][i-1].second);
			par[u][i] = {jump, weight};
        }

		for (ii v : adj[u]) {
			if (v.first != p)
				dfs(v.first, u, d+1, v.second);
		}
	}
	ii ascend(int u, int k) {
        ll dist = 0;
		for (int i = 0; i <= l; i++)
			if (k & (1 << i)){
                dist = max(par[u][i].second, dist);
				u = par[u][i].first;
            
            }
		return {u, dist};
	}
	bool is_anc(int u, int v) {
		if (dep[u] < dep[v])
			swap(u, v);
		return ascend(u, dep[u]-dep[v]).first == v;
	}
	ll lca(int u, int v) {
        ll dist = 0;

		if (dep[u] > dep[v]){
            ii temp = ascend(u, dep[u]-dep[v]);
			u = temp.first;
            dist = max(temp.second, dist);
        }
		if (dep[v] > dep[u]){
			ii temp = ascend(v, dep[v]-dep[u]);
            v = temp.first;
            dist = max(temp.second, dist);
        }
		if (u == v)
			return dist;

		for (int i = l; i >= 0; i--) {
			if (par[u][i].first != par[v][i].first) {
                dist = max(dist, max(par[u][i].second, par[v][i].second));
				u = par[u][i].first;
				v = par[v][i].first;
			}
		}
		return max(max(par[u][0].second, par[v][0].second), dist);
	}
};

struct edge {
    ll u, v, w;
};

int main(){
    ll n, m; cin >> n >> m;
    vector<edge> edges;
    graph g(n);
    for (int i = 0; i < m; i++){
        ll u, v, w; cin >> u >> v >> w; u--; v--;
        edge e;
        e.u = u+1;
        e.v = v+1;
        e.w = w;
        g.add_edge(u, v, w);
        edges.push_back(e);
    }

    viii res;
    ll cnt = 0;
    vector<bool> vis(n, false);
    g.prim(res, 0, vis);


    graph1 tree(n+1);
    for (auto cur : res) {
        tree.adj[cur.second.first+1].push_back({cur.second.second+1, cur.first});
        tree.adj[cur.second.second+1].push_back({cur.second.first+1, cur.first});
    }
    for (auto cur : res){
        cnt += cur.first;
    }
    tree.adj[0].push_back({1, 0});
    tree.adj[1].push_back({0, 0});

    tree.dfs(1, 0, 0, 0);

    for (int i = 0; i < m; i++){
        edge cur = edges[i];

        cout << cnt+cur.w-tree.lca(cur.u, cur.v) << endl;
    }
}