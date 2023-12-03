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

void dijkstra(int src, vector<ll>& dist, vector<bool>& done, vector<vector<pair<ll, ll>>>& adj) {
    dist[src] = 0;
    set<pair<ll, ll>> q;
    q.insert({dist[src], src});

    while (q.size() > 0) {
        ll u = (*q.begin()).second; q.erase(q.begin());

        if (!done[u]) {
            for (pair<ll, ll> e : adj[u]) {
                ll v = e.second;
                ll w = e.first;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    q.insert({dist[v], v});
                }
            }
            done[u] = true;
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;

    vector<vector<ll>> flightTime(n+1, vector<ll>(n+1, 0));
    vector<ll> inspectionTime(n+1, 0);
    vector<vector<ll>> flights;
    vector<vector<ll>> graph(m+1, vector<ll>());
    flow_network f(2*m+2, 0, 2*m+1);

    for (int i = 0; i < n; ++i) {
        ll temp;
        cin >> temp;
        inspectionTime[i+1] = temp;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ll temp;
            cin >> temp;
            flightTime[i+1][j+1] = temp;
        }
    }

    vector<vector<ll>> shortestPath(n+1, vector<ll>(n+1));
    vector<vector<pair<ll, ll>>> adj(n+1, vector<pair<ll, ll>>(n+1));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i == j) continue;
            adj[i].push_back({flightTime[i][j]+inspectionTime[j], j});
        }
    }

    for (int i = 1; i <= n; i++){
        vector<ll> dist(n+1, INF);
        vector<bool> done(n+1, false);
        dijkstra(i, dist, done, adj);
        shortestPath[i] = dist;
    }

    vector<vector<set<ll>>> test(n+1, vector(n+1, set<ll>()));
    for (int i = 1; i <= m; ++i) {
        ll a, b, t;
        cin >> a >> b >> t;
        flights.push_back({i, a, b, t});
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == j) continue;

            vector<ll> flight1, flight2;

            flight1 = flights[i];
            flight2 = flights[j]; 

            if (flightTime[flight1[1]][flight1[2]] + inspectionTime[flight1[2]] + flight1[3] + shortestPath[flight1[2]][flight2[1]] <= flight2[3]){
                graph[flight1[0]].push_back(flight2[0]);
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        vector<ll> current = graph[i];
        for (int j = 0; j < current.size(); ++j) {
            f.add_edge(i, current[j]+m, 1);
        }
    }

    for (int i = 1; i <= m; ++i) {
        f.add_edge(0, i, 1);
    }

    for (int i = 1; i <= m; ++i) {
        f.add_edge(i+m, 2*m+1, 1);
    }

    ll ans = f.max_flow();
    //cout << ans << endl;
    cout << m-ans << endl;


    return 0;
}
