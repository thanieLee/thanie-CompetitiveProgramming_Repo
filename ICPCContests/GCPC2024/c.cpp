#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct frac{
    int p, q;

    frac(int x, int y = 1){
        p = x;
        q = y;
        reduce();
    }

    void reduce(){
        if (p == 0) {
            q = 1;
            return;
        }
        if (q == 0) return;
        int d = gcd(p, q);
        p = p/d;
        q = q/d;
    }

    frac operator+ (frac y) {
        frac cur = *this;
        int prevq = cur.q;
        cur.q = lcm(cur.q, y.q);
        cur.p = cur.p*(cur.q/prevq) + y.p*(cur.q/y.q);
        cur.reduce();
        return cur;
    }

    frac operator- (frac y) {
        frac cur = *this;
        int prevq = cur.q;
        cur.q = lcm(cur.q, y.q);
        cur.p = cur.p*(cur.q/prevq) - y.p*(cur.q/y.q);
        cur.reduce();
        return cur;
    }

    frac operator* (frac y){
        frac cur = *this;
        cur.p = cur.p*y.p;
        cur.q = cur.q*y.q;
        cur.reduce();
        return cur;
    }

    frac operator/ (frac y){
        frac cur = *this;
        cur.p = cur.p*y.q;
        cur.q = cur.q*y.p;
        cur.reduce();
        return cur;
    }

    frac operator += (frac y){
        *this + y;
        return *this;
    }
};

bool cmp(frac x, frac y){
    return ((double) (x.p/x.q)) < ((double) (y.p/y.q));
}

void dfs(int u, vector<int> &dist, vector<bool> &vis, int dep, vector<vector<int>> &adj){
    vis[u] = true;
    dist[u] = dep;

    deque<int> sta;
    sta.push_back(u);

    while (!sta.empty()){
        int cur = sta.front();
        sta.pop_front();
        vis[cur] = true;

        for (int v : adj[cur]) {
            if (dist[v] == -1) {
                sta.push_back(v);
                dist[v] = dist[cur]+1;
            }
        }

    }
}

int main(){
    int n, m, k; cin >> n >> m >> k;
    vector<bool> isWormhole(n, false);
    vector<int> wormholes;
    for (int i = 0; i < k; i++){
        int ki; cin >> ki; ki--;
        isWormhole[ki] = true;
        wormholes.push_back(ki);
    }

    vector<vector<int>> graph(n, vector<int>());
    vector<frac> dp(n, frac(-1, -1));

    for (int i = 0; i < m; i++){
        int a, b; cin >> a >> b; a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }


    vector<int> dist(n, -1);
    int dep = 0;
    vector<bool> vis(n, false);
    dfs(n-1, dist, vis, dep, graph);
    vector<vector<int>> test(n+1, vector<int>());
    int total = 0;
    for (int i = 0; i < n; i++){
        if (isWormhole[i]) {
            total += dist[i];
        }
    }


    vector<int> val(n, -1);
    for (int i = 0; i < n; i++){
        if (isWormhole[i]){
            val[i] = total-dist[i];
        }
    }

    frac ans = frac(dist[0], 1);
    for (int i = 0; i < n; i++){
        if (isWormhole[i]) {
            ans = min(ans, frac(val[i]+dist[i], k-1), cmp);
        }
    }

    cout << ans.p << "/" << ans.q << endl;
}