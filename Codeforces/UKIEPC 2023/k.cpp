#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

vector<bool> visited, removed, finished;
vector<vector<pii>> adj;
vector<int> cost;
set<pii> sort;
void dfs(int u, int prev_id) {
    //cout << u << " " << prev_id << endl;

    if (visited[u]) {
        removed[prev_id] = true;
        return;
    }

	visited[u] = true;
	
	for (auto p : adj[u])  {
        int v = p.first;
        int id = p.second;
        //cout << v << " | " << id << endl;
        if (!removed[id] and !finished[v])
		    dfs(v, id);
    }
    visited[u] = false;
    finished[u] = true;
}

int main(){
    int n, m; cin >> n >> m;
    
    adj.resize(n, vector<pii>());
    vector<set<pii>> set_adj(n, set<pii>());
    vector<vector<int>> repeats(m, vector<int>());
    vector<bool> active(m, false);
    removed.resize(m, false);
    visited.resize(n, false);
    finished.resize(n, false);
    cost.resize(m, 0);
    
    for (int i = 0; i < m; i++) {
        int ai, bi; cin >> ai >> bi; ai--; bi--;
        cout << i << endl;
        if (set_adj[ai].lower_bound({bi, -1})->first != bi) {
            cout << "why" << endl;
            adj[ai].push_back({bi, i});
            set_adj[ai].insert({bi, i});
            cost[i]++;
            repeats[i].push_back(i+1);
            active[i] = true;
        } else {
            int id = set_adj[ai].lower_bound({bi, -1})->second;
            cost[id]++;
            repeats[id].push_back(i+1);
        }
    }

    dfs(0, -1);
    
    // for (int i = 0; i < m; i++) {
    //     cout << removed[i] << ' ';
    // }
    // cout << endl;
    int cnt = 0;

    for (int i = 0; i < m; i++) {
        if (!active[i]) continue;
        if (removed[i]) continue;

        for (auto rep : repeats[i]) {
            cnt++;
            cout << rep << " " << endl;
        }
    }

    cout << cnt << endl;
    if (cnt >= m/2) {
        cout << "YES" << endl;
        cout << cnt << endl;
        for (int i = 0; i < m; i++) {
            if (!active[i]) continue;
            if (removed[i]) continue;

            for (auto rep : repeats[i]) {
                cout << rep << " ";
            }
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
}