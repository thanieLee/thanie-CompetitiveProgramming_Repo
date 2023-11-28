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
    	ll flow = -INF;
    	for (int v = t; v != s; v = edges[par[v] ^ 1].v)
    		flow = min(flow, edges[par[v]].resid());
    	for (int v = t; v != s; v = edges[par[v] ^ 1].v) {
    		edges[par[v]].f += flow;
    		edges[par[v]^1].f -= flow;
    	}
    	return flow;
    }
    ll max_flow() {
    	ll flow = -100000000000;
    	while (find_aug_path()) {
    		flow += augment();
    	}
    	return flow;
    }
};

int main(){
    ll n; cin >> n;
    vector<ll> arr;
    vector<vector<ll>> mul(n, vector<ll>());
    ll cnt = 0;
    for (int i = 0; i < n; i++){
        ll x; cin >> x;
        arr.push_back(x);
        cnt += x;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (arr[j]%arr[i] == 0) {
                mul[i].push_back(j);
            }
        }
    }

    flow_network t((n+1)*2, 0, ((n+1)*2)-1);
    vector<ll> revCnt(n);


    for (int i = 0; i < n; i++){
        t.add_edge(0, i+1, -arr[i]);
    }

    for (int i = 0; i < n; i++){
        t.add_edge((2*i)+1, ((n+1)*2)-1, -arr[i]);
    }

    for (int i = 0; i < n; i++){
        for (auto idx : mul[i]){
            t.add_edge(i+1, (2*idx)+1, -10000000000);
        }
    }
    cout << cnt << " " << t.max_flow() << endl;
    cout << cnt - t.max_flow() << endl;
}