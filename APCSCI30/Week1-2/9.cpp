#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define INF 1000000000000
#define MAX 1000000000

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
    cout << 1%(-1) << endl;
    ll n; cin >> n;
    vector<ll> arr;
    vector<vector<ll>> mul(n, vector<ll>());
    ll cnt = 0;
    for (int i = 0; i < n; i++){
        ll x; cin >> x;
        arr.push_back(x);
        cnt += x;
    }

    sort(arr.begin(), arr.end());
    for (ll i : arr) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if ((j+1)%(i+1) == 0 and abs((j+1)/(i+1)) >= 2) {
                mul[i].push_back(j+1);
            }
        }
    }

    flow_network t(n+2, 0, n+1);
    vector<vector<bool>> done(n+3, vector<bool>(n+3, false));
    vector<ll> revCnt(n);

    for (int i = 1; i <= n; i++) {
        if (!done[0][i]){
            t.add_edge(0, i, -arr[i-1]+MAX);
            done[0][i] = true;
        }
            
        cout << 0 << " " << i << " " << arr[i-1] << " " << MAX << endl;
        for (int j = 1; j < mul[i-1].size()-1; j++) {
            if (j < mul[i-1].size()-1) continue;

            if (!done[mul[i-1][j-1]][mul[i-1][j]]){
                t.add_edge(mul[i-1][j-1], mul[i-1][j], INF);
                done[mul[i-1][j-1]][mul[i-1][j]] = true;
            }
            
            //cout << mul[i-1][j-1] << " | " << mul[i-1][j] << endl;
        }
        if (!done[mul[i-1][mul[i-1].size()-1]][n+1]){
            t.add_edge(mul[i-1][mul[i-1].size()-1], n+1, INF);
            done[mul[i-1][mul[i-1].size()-1]][n+1] = true;
        }
        for (int b : mul[i-1]) {
            cout << b << " ";
        }
        cout << endl << endl;
        cout << mul[i-1][mul[i-1].size()-1] << " | " << n+1 << endl;
    }

    for (int i = 0; i <= n+1; i++) {
        for (int e : t.adj[i]) {
            cout << i << " " << t.edges[e].v << " " << t.edges[e].f << " " << t.edges[e].c << endl;
        }
    }

    cout << "test" << endl;
    ll ans = t.max_flow();
    cout << cnt << " " << ans << endl;
    ll temp = cnt-ans;
    cout << temp << endl;
    for (int i = 1; i <= n; i++) {
        for (int e : t.adj[i]) {
            if (t.edges[e].v == n+1 and t.edges[e].f > 0) {
                temp += MAX;
            }
        }
    }

    cout << temp << endl;
}