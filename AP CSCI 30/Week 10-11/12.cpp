#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef long double ld;
typedef vector<int> vint;
typedef pair<int, int> pint;
#define MAX 1000000000
#define rep(i, n) for (int i = 0; i < n; i++)
#define revrep(i, n) for (int i = n-1; i >= 0; i--)
#define repk(i, n, k) for (int i = k; i < n; i++)

int cycleCount = 0;
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
};

void dfs(int u, vector<bool>& visited, vector<int>& adj, vector<int> &inCycle){
    if (visited[u]){
        return;
    }

    deque<int> q;

    int cur = u;
    q.push_back(u);
    vector<bool> tempVisited(visited.size(), false);
    while (!visited[q.back()]){
        cur = q.back();
        visited[cur] = true;
        tempVisited[cur] = true;
        q.push_back(adj[cur]);
    }
    deque<int> copy = q;
    if (!tempVisited[q.back()]) return;
    cycleCount++;
    cout << u << " " << cur << " " << q.back() << endl;
    q.pop_back();
    
    while (q.back() != u) {
        inCycle[q.back()] = cycleCount;
        q.pop_back();
    }
    inCycle[q.back()] = cycleCount;
    q.pop_back();
}

int main(){
    int n, q; cin >> n >> q;
    vector<int> adj(n), inCycle(n, 0);

    for (int i = 0; i < n; i++) {
       int a; cin >> a;
       adj[i] = a-1;
    }

    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        dfs(i, visited, adj, inCycle);
    }
    
    for (int i = 0; i < n; i++) {
        cout << inCycle[i] << " ";
    }
    cout << "test" << endl;
}