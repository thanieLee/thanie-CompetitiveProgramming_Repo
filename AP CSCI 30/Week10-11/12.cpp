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
    vector<vector<int>> par, cyclePar;
    vector<int> dep, adj, cycleDep, cycleAdj, inCycle;

 
    graph(int n) : n(n) {
        l = ceil(log2(n));
        dep.resize(n);
        adj.resize(n);
        par.resize(n, vector<int>(l+1));
        cycleDep.resize(n);
        cycleAdj.resize(n);
        cyclePar.resize(n, vector<int>(l+1));
    }
    void addCycle(vector<int> cycle){
        inCycle = cycle;
    }

    void processCycles(){
        vector<bool> cycleCut(cycleCount+1, false);
        cycleCut[0] = true;
        cycleAdj = adj;
        for (int i = 0; i < n; i++) {
            //cout << i << endl;
            if (cycleCut[inCycle[i]]) continue;
            cycleCut[inCycle[i]] = true;
            cycleAdj[i] = i;
        }
        
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            cycleDfs(i, 0, visited);
        }
    }

    void dfs(int u, int d, vector<bool> &visited) {
        //cout << "poo" << endl;
        //cout << u << " " << visited[u] << " " << inCycle[u] << endl;
        if (visited[u]) return;
        if (inCycle[u] != 0) {
            dep[u] = d;
            return;
        }
        visited[u] = true;
    
        dep[u] = d;
        par[u][0] = adj[u];
        //cout << "testing" <<  " " << u << " " << adj[u] << endl;
        for (int i = 1; i <= l; i++)
            par[u][i] = par[par[u][i-1]][i-1];
    
 
        dfs(adj[u], d+1, visited);
    }

    void cycleDfs(int u, int d, vector<bool> &visited) {
        if (visited[u]) return;
        if (inCycle[u] == 0) return;
        visited[u] = true;
        cycleDep[u] = d;
        cyclePar[u][0] = cycleAdj[u];
        for (int i = 1; i <= l; i++)
            cyclePar[u][i] = cyclePar[cyclePar[u][i-1]][i-1];

        cycleDfs(adj[u], d+1, visited);
    }
    int ascend(int u, int k) {
        for (int i = 0; i <= l; i++)
            if (k & (1 << i))
                u = par[u][i];
        return u;
    }
    bool is_anc(int u, int v) {
        return climbTest(u, v);
    }
    pair<int, int> lca(int u) {
        //cout << u << endl;
        int cnt = 0;
        for (int i = l; i >= 0; i--) {
            if (inCycle[par[u][i]] == 0) {
                //cout << i << " " << par[u][i] << endl;
                u = par[u][i];
                cnt += 1<<i;
            }
        }
        return {par[u][0], cnt+1};
    }

    int climb(int u, int v){
        int cnt1 = 0;
        for (int i = l; i >= 0; i--) {
            if (inCycle[par[u][i]] == 0) {
                //cout << i << " " << par[u][i] << endl;
                u = par[u][i];
                cnt1 += 1<<i;
            }
        }

        int cnt2 = 0;
        for (int i = l; i >= 0; i--) {
            if (inCycle[par[v][i]] == 0) {
                //cout << i << " " << par[u][i] << endl;
                v = par[v][i];
                cnt2 += 1<<i;
            }
        }
        
        cout << cnt1 << " " << cnt2 << endl;
        return abs(cnt1 - cnt2);
    }

    bool climbTest(int u, int v){
        int cnt1 = 0;
        cout << u << " " << v << endl;
        for (int i = l; i >= 0; i--) {
            if (inCycle[par[u][i]] == 0) {
                cout << i << " " << par[u][i] << " " << u << " " << v << endl;
                //cout << i << " " << par[u][i] << endl;
                u = par[u][i];
                cnt1 += 1<<i;
            }
        }
        cout << u << " " << v << endl;
        int cnt2 = 0;
        for (int i = l; i >= 0; i--) {
            if (inCycle[par[v][i]] == 0) {
                //cout << i << " " << par[u][i] << endl;
                v = par[v][i];
                cnt2 += 1<<i;
            }
        }
        cout << u << " " << v << endl;
        return par[u][0] == par[v][0];
    }
};

void dfs(int u, vector<bool>& visited, vector<int>& adj, vector<int> &inCycle, vector<int> &cycleSize){
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
    //cout << u << " " << cur << " " << q.back() << endl;
    int cnt = 0;
  
    while (inCycle[q.back()] != cycleCount) {
        inCycle[q.back()] = cycleCount;
        cnt++;
        q.pop_back();
    }

    cycleSize.push_back(cnt);
}

int main(){
    int n, q; cin >> n >> q;
    vector<int> adj(n), inCycle(n, 0);
    graph g(n);
    for (int i = 0; i < n; i++) {
       int a; cin >> a;
       adj[i] = a-1;
       g.adj[i] = a-1;
    }

    vector<bool> visited(n, false);
    vector<int> cycleSize;

    for (int i = 0; i < n; i++) {
        dfs(i, visited, adj, inCycle, cycleSize);
    }
    
    for (int i = 0; i < n; i++) {
        cout << inCycle[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        if (inCycle[i] == 0) continue;
        for (int j = 0; j < g.l; j++) {
           g.par[i][j] = i;
        }
    }
    g.addCycle(inCycle);
    visited.clear();
    visited.resize(n, false);
    for (int i = 0; i < n; i++) {
        g.dfs(i, 0, visited);
    }

    g.processCycles();

    
    //cout << endl;

    for (int i = 0; i < n; i++) {
        //cout << i << " " << g.cycleAdj[i] << endl;
    }

    for (int i = 0; i < cycleSize.size(); i++) {
        //cout << cycleSize[i] << endl;
    }

    for (int i = 0; i < q; i++) {
        cout << "query: " << i+1 << endl;
        int a, b; cin >> a >> b;
        a--;
        b--;
        if (inCycle[a] == 0 and inCycle[b] == 0) {
            cout << g.is_anc(a, b) << endl;
            if (!g.is_anc(a, b)) {
                cout << -1 << endl;
            } else {
                cout << g.climb(a, b) << endl;
            }
        } else if (inCycle[a] != 0 and inCycle[b] != 0){
            if (inCycle[a] != inCycle[b]) {
                cout << -1 << endl;
            } else {
                //cout << g.cycleDep[a] << " " << g.cycleDep[b] << endl;
                if (g.cycleDep[a] <= g.cycleDep[b])
                    cout << abs(g.cycleDep[a] - g.cycleDep[b]) << endl;
                else
                    cout << cycleSize[inCycle[a]-1] - abs(g.cycleDep[a] - g.cycleDep[b]) << endl;
            }
        } else {
            if (inCycle[b] == 0) {
                swap(a, b);
            }
            pair<int, int> test = g.lca(a);
            int entrance =  test.first;
            //cout  << entrance << " test" << endl;
            if (inCycle[entrance] != inCycle[b]) {
                cout << -1 << endl;
            } else {
                int temp;
            
                if (g.cycleDep[entrance] <= g.cycleDep[b])
                    temp = abs(g.cycleDep[entrance] - g.cycleDep[b]);
                else
                    temp = cycleSize[inCycle[entrance]-1] - abs(g.cycleDep[entrance] - g.cycleDep[b]);
                
                cout << test.second + temp << endl;
            }
        }
    }
    cout << g.par[0][1] << endl;
}