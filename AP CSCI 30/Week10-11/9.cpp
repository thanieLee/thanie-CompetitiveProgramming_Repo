#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
struct three{
    int node, parent, depth;
 
    three(int n, int p, int d){
        node = n;
        parent = p;
        depth = d;
    }
};
 
struct graph {
    int n, l;
    vector<vector<int>> par;
    vector<int> dep, adj;
 
    graph(int n) : n(n) {
        l = ceil(log2(n));
        dep.resize(n);
        adj.resize(n);
        par.resize(n, vector<int>(l+1));
    }
    void dfs(int u, int p, int d) {
        dep[u] = d;
        par[u][0] = p;
        for (int i = 1; i <= l; i++)
            par[u][i] = par[par[u][i-1]][i-1];
 
        dfs(adj[u], u, d+1);
    }
//    void dfs(int u, int p) {
//        dep[u] = 0;
//        stack<three> sta;
//        sta.push(three(u, p, 0));
//        while (!sta.empty()) {
//            //cout << sta.size() << endl;
//            three cur = sta.top();
//
//            dep[cur.node] = cur.depth;
//            sta.pop();
//            par[cur.node][0] = cur.parent;
//            for (int i = 1; i < l; ++i) {
//                int val = par[cur.node][i - 1];
//                par[cur.node][i] = par[val][i - 1];
//            }
//            for (int k: adj[cur.node]) {
//                if (k != cur.parent) {
//                    sta.push(three(k, cur.node, cur.depth + 1));
//                }
//            }
//        }
//    }
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
 
int main(){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0);
    int n, q; cin >> n >> q;
    graph g(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b; cin >> a >> b;
        a--; b--;
    }
    g.dfs(0, 0, 0);
    for (int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;
        a--; b--;
        int anc = g.lca(a, b);
        int plus = g.dep[a]+g.dep[b];
        cout << plus-g.dep[anc]*2 << endl;
    }
 
    gettimeofday(&end, NULL);
 
 
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec -start.tv_usec)) * 1e-6;
    //cout << fixed << time_taken << setprecision(10) << endl;
 
}