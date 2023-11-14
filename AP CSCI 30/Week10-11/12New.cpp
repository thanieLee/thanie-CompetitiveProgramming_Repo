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
int l;
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
int ascend(int u, int k, vector<vector<int>> &par){
    for (int i = l; i >= 0; i--){
        if (k & (1<<i)) {
            u = par[u][i];
        }
    }

    return u;
}

bool is_anc(int u, int v, vector<int> &inCycle, vector<vector<int>> &par){
    int cnt1 = 0;
    int origU = u, origV = v;
    for (int i = l; i >= 0; i--){
        if (inCycle[par[u][i]] == 0){
            u = par[u][i];
            cnt1 += 1<<i;
        }
    }
    int cnt2 = 0;
    for (int i = l; i >= 0; i--){
        if (inCycle[par[v][i]] == 0){
            v = par[v][i];
            cnt2 += 1<<i;
        }
    }

    return (ascend(origU, cnt1-cnt2, par) == origV);
}


int climb(int u, vector<int> &inCycle, vector<vector<int>> &par){
    int cnt = 1;

    for (int i = l; i >= 0; i--){
        //cout << u << " " << i << " " << par[u][i] << endl;
        if (inCycle[par[u][i]] == 0){
            u = par[u][i];
            cnt += 1<<i;
        }
    }

    return cnt;
}

int climbEntrance(int u, vector<int> &inCycle, vector<vector<int>> &par){
    int cnt = 1;

    for (int i = l; i >= 0; i--){
        if (inCycle[par[u][i]] == 0){
            u = par[u][i];
            cnt += 1<<i;
        }
    }

    return par[u][0];
}

int main(){
    int n, q; cin >> n >> q;
    vector<int> adj(n);
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 0; i < n; i++) {
        int a; cin >> a; a--;
        adj[i] = a;
    }
    l = ceil(log2(n));
    vector<int> inCycle(n, 0);
    vector<int> cycleSize;
    vector<bool> visited(n, false);

    vector<int> cycleDistance(n);
    vector par(n, vector<int>(l+1));
    for (int i = 0; i < n; i++) {
        dfs(i, visited, adj, inCycle, cycleSize);
    }
    vector<bool> cycleProcessed(cycleCount+1, false);

    for (int i = 0; i < n; i++) {
       if (inCycle[i] == 0) continue;
       for (int j = 0; j < l+1; j++){
            par[i][j] = i;
       }
    }

    for (int i = 0; i < n; i++) {
        if (inCycle[i] != 0) continue;
        par[i][0] = adj[i];
    }
    
    for (int j = 1; j <= l; j++){
        for (int i = 0; i < n; i++){
            if (inCycle[i] != 0) continue;
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }


    for (int i = 0; i < n; i++){
        if (inCycle[i] == 0) continue;
        if (cycleProcessed[inCycle[i]]) continue;
        cycleProcessed[inCycle[i]] = true;
        int cnt = 0;
        int cur = adj[i];
        while(cur != i) {
            cnt++;
            cycleDistance[cur] = cnt;
            cur = adj[cur];
        }
        //cycleDistance[i] = cnt+1;
    }
    for (int i = 0; i < n; i++) {
       //cout << cycleDistance[i] << " ";
    }

    for (int i = 0; i < q; i++){
        int a, b; cin >> a >> b; a--; b--;
        //cout << "query " << i+1 << ":" << endl;
        //cout << a << " " << b << endl;
        //cout << inCycle[a] << " " << inCycle[b] << endl;
        if (a == b) {
            cout << 0 << '\n';
            continue;
        }
        //cout << is_anc(a, b, inCycle, par) << endl;
        if (!is_anc(a, b, inCycle, par) and inCycle[a] == 0 and inCycle[b] == 0) {
            //cout << 1 << " hehe" << endl;
            cout << -1 << '\n';
        } else if (inCycle[a] == 0 and inCycle[b] == 0){
            //cout << 2 << endl;
            //cout << abs(climb(a, inCycle, par)) << " " << climb(b, inCycle, par) << endl;
            cout << abs(climb(a, inCycle, par) - climb(b, inCycle, par)) << '\n';
        } else if (inCycle[a] != 0 and inCycle[b] != 0) {
    
            //cout << 3 << endl;
            if (inCycle[a] != inCycle[b]) {
                cout << -1 << '\n';
            } else {
                //cout << cycleDistance[a] << " " << cycleDistance[b] << " " << cycleSize[inCycle[a]-1] <<  endl;
                //cout << abs(cycleDistance[a] - cycleDistance[b]) << " " << abs((cycleDistance[a]-cycleSize[inCycle[a]-1]) - cycleDistance[b]) << endl;

                if (cycleDistance[a] > cycleDistance[b]) {
                    cout << cycleSize[inCycle[a]-1]-abs(cycleDistance[a] - cycleDistance[b]) << '\n';
                } else {
                    cout << abs(cycleDistance[a] - cycleDistance[b]) << '\n';
                }
            }
        } else {

            if (inCycle[b] == 0){
                cout << -1 << endl;
                continue;
            }
    
            int entrance = climbEntrance(a, inCycle, par);

            if (inCycle[entrance] != inCycle[b]) {
                cout << -1 << '\n';
            } else {
                if (cycleDistance[entrance] > cycleDistance[b])
                    cout << climb(a, inCycle, par) + (cycleSize[inCycle[entrance]-1])-abs(cycleDistance[entrance] - cycleDistance[b]) << '\n';
                else
                    cout << climb(a, inCycle, par) + abs(cycleDistance[entrance] - cycleDistance[b]) << '\n';
            }
        }
    }

    
    
}