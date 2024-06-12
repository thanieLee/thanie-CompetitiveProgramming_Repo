#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<ll> ans;
ll k;
vector<vector<int>> graph;
void dfs(int u, int p, int dep) {
    //cout << u << " " << dep << endl;
    if (graph[u].size() == 1 and dep != 0) return;
    if (dep == 0) {
        ans[u] = k;
        int cnt = 1;
        for (auto v : graph[u]) {
            if (v != p) {
                ans[v] = max(k-cnt, 0ll);
                cnt++;
                dfs(v, u, dep+1);
            }
        }
    } else {
        int cnt = 2;
        for (auto v : graph[u]) {
            if (v != p) {

                ans[v] = max(k-cnt, 0ll);
                cnt++;
                dfs(v, u, dep+1);
            }
        }
    }
}



int main() {
    ll n; cin >> n >> k;
    graph.resize(n, vector<int>());
    ans.resize(n);
    vector<int> vis(n, false);
    vis[0] = true;
    for (int i = 0; i < n-1; i++){
        int ai, bi; cin >> ai >> bi; ai--; bi--;
        graph[ai].push_back(bi);
        graph[bi].push_back(ai);
    }

    dfs(0, -1, 0);

    ll cnt = 1;
    for (int i = 0; i < n; i++) {
        cnt *= ans[i];
        cnt %= 1000000007ll;
    }
    cout << cnt << endl;
}