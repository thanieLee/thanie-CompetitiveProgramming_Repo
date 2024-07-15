#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int n, m, q; 
vector<map<int, int>> adj, mst_adj;
vector<int> parent, ranking, siz;

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void connect(int i, int j) {
    int u = find(i);
    int v = find(j);
   
    if (u == v)
        return;
    if (ranking[u] < ranking[v]) {
        parent[u] = v;
        ranking[v] += ranking[u];
    } else {
        parent[v] = u;
        ranking[u] += ranking[v];
    }
}


struct graph {
	int n, l;
	vector<vector<pii>> par;
    vector<map<int, int>> adj;
	vector<int> dep;
 
	graph(int n) : n(n) {
		l = ceil(log2(n));
		dep.resize(n);
		adj.resize(n, map<int, int>());
		par.resize(n, vector<pii>(l+1));
	}
 
	void dfs(int u, int p, int d, int w) {
		dep[u] = d;
		par[u][0] = {p, w};
		for (int i = 1; i <= l; i++){
            int jump = par[par[u][i-1].first][i-1].first;
            int weight = max(par[u][i-1].second, par[par[u][i-1].first][i-1].second);
            par[u][i] = {jump, weight};
        }
		for (pii v : adj[u]) {
			if (v.first != p)
				dfs(v.first, u, d+1, v.second);
		}
	}
	pii ascend(int u, int k) {
        int dist = 0;
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
	pii lca(int u, int v) {
        int dist = 0;
        int start_u = u, start_v = v;
		if (dep[u] > dep[v]){
            pii temp = ascend(u, dep[u]-dep[v]);
			u = temp.first;
            dist = max(temp.second, dist);
        }
		if (dep[v] > dep[u]){
			pii temp = ascend(v, dep[v]-dep[u]);
            v = temp.first;
            dist = max(temp.second, dist);
        }

		if (u == v) {
            if (dep[start_u] > dep[start_v]) {
                return {v, dist};
            } else {
                return {u, dist};
            }
        }
			
 
		for (int i = l; i >= 0; i--) {
			if (par[u][i].first != par[v][i].first) {
                dist = max(dist, max(par[u][i].second, par[v][i].second));
				u = par[u][i].first;
				v = par[v][i].first;
			}
		}

		return {par[u][0].first, max(max(par[u][0].second, par[v][0].second), dist)};
	}
};

bool cmp1(pair<pii, pii> x, pair<pii, pii> y) {
    return x.second.second < y.second.second;
}

int main(){
    cin >> n >> m >> q;
    adj.resize(n, map<int, int>());
    vector<pair<int, pii>> queries, roads;
    parent.resize(n);
    ranking.resize(n, 1);
    mst_adj.resize(n, map<int, int>());
    
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v, t; cin >> u >> v >> t; u--; v--;
        adj[u][v] = t;
        adj[v][u] = t;
        roads.push_back({t, {u, v}});
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b; a--; b--;
        queries.push_back({i, {a, b}});
    }

    sort(roads.begin(), roads.end());

    for (int i = 0; i < m; i++) {
        int u = roads[i].second.first;
        int v = roads[i].second.second;
        int t = roads[i].first;

        if (find(u) != find(v)) {
            mst_adj[u][v] = t;
            mst_adj[v][u] = t;
            connect(u, v);
        }
    }

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ranking[i] = 1;
    }

    graph mst(n);
    mst.adj = mst_adj;
    mst.dfs(0, 0, 0, -1);
    vector<pair<pii, pii>> final_queries;
    for (int i = 0; i < q; i++) {
        pair<int, pii> cur_query = queries[i];
        int a = cur_query.second.first;
        int b = cur_query.second.second;
        pii ans = mst.lca(a, b);
        final_queries.push_back({{a, b}, {cur_query.first, ans.second}});
    }
    
    sort(final_queries.begin(), final_queries.end(), cmp1);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ranking[i] = 1;
    }

    int road_idx = 0;
    vector<pair<int, pii>> ans;

    for (auto que : final_queries) {
        //cout << que.first.first << " " << que.first.second << " " << que.second.first << " " << que.second.second << endl;
        if (road_idx < m) {
            while (roads[road_idx].first <= que.second.second) {
                connect(roads[road_idx].second.first, roads[road_idx].second.second);
                road_idx++;
                if (road_idx == m) break;
            }
        }

        ans.push_back({que.second.first, {que.second.second, ranking[find(que.first.first)]}});
        //cout << que.second.second << " " << que.second.first << " " << ranking[find(que.first.first)] << endl;
    }

    sort(ans.begin(), ans.end());

    for (int i = 0; i < q; i++) {
        cout << ans[i].second.first << " " << ans[i].second.second << endl;
    }
}