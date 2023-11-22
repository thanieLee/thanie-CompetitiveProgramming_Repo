#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define INF 10000000000

struct edge {
    size_t i;
    int v;
    ll c, f;
    ll resid() { return c - f; }
};

struct flow_network {
    vector<edge> edges;
    vector<vector<int>> adj;
    vector<int> par;
    int n, s, t;

    flow_network(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        par.resize(n);
    }

    void changeST(int s1, int t1) {
        s = s1;
        t = t1;
    }

    void add_edge(int u, int v, ll cap) {
        edges.push_back({edges.size(), v, cap, 0});
        adj[u].push_back(edges.size()-1);
        edges.push_back({edges.size(), u, 0, 0});
        adj[v].push_back(edges.size()-1);
    }

    bool find_aug_path() {
    	fill(par.begin(), par.end(), -1);
    	par[s] = -2;
    	queue<int> q;
    	q.push(s);
    	while (!q.empty()) {
    		int u = q.front(); q.pop();
    		if (u == t)
    			break;
    		for (int i : adj[u]) {
    			edge& e = edges[i];
    			if (e.resid() > 0 && par[e.v] == -1) {
    				par[e.v] = e.i;
    				q.push(e.v);
    			}
    		}
    	}
    	return par[t] != -1;
    }
    ll augment() {
    	ll flow = INF;
    	for (int v = t; v != s; v = edges[par[v] ^ 1].v)
    		flow = min(flow, edges[par[v]].resid());
    	for (int v = t; v != s; v = edges[par[v] ^ 1].v) {
    		edges[par[v]].f += flow;
    		edges[par[v]^1].f -= flow;
    	}
    	return flow;
    }
    ll max_flow() {
    	ll flow = 0;
    	while (find_aug_path()) {
    		flow += augment();
    	}
    	return flow;
    }
};

int main(){
    int H, W; cin >> H >> W;
    vector graph(H, vector<bool>(W, false));
    pair<int, int> start, end;
    for (int i = 0; i < H; i++){
        string s; cin >> s;
        for (int j = 0; j < W; j++){
            if (s[j] != '.') { 
                graph[i][j] = true;
            }

            if (s[j] == 'S'){
                start = {i, j};
            }
            if (s[j] == 'T'){
                end = {i, j};
            }
        }
    }
    
    if (start.first == end.first or start.second == end.second) {
        cout << -1 << endl;
        return 0;
    }

    flow_network t(H*W, start.first, end.second+H);

    for (int i = 0; i < H; i++){
        for (int j = 0; j < W; j++){
            if (graph[i][j]) {
                //cout << i << " " << j << endl;
                t.add_edge(i, H+j, 1);
                t.add_edge(H+j, i, 1);
            }
        }
    }

    ll ans = 0;
    ans += t.max_flow();
    t.changeST(start.second+H, end.first);
    ans += t.max_flow();
    t.changeST(start.first, end.first);
    ans += t.max_flow();
    t.changeST(start.second+H, end.second+H);
    ans += t.max_flow();
    cout << ans << endl;


}