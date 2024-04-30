#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<int> colors;
vector<int> ans;
void dfs(int u, int p, vector<vector<int>> &adj, vector<set<int>*> &colorSet) {
    int largest = -1;
    vector<int> child;

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, adj, colorSet);
            child.push_back(v);
            if (largest == -1 or colorSet[v]->size() > colorSet[largest]->size()) {
                largest = v;
            }
        }
    }

    if (largest == -1) {
        colorSet[u] = new set<int>;
    } else {
        colorSet[u] = colorSet[largest];
    }
    for (int v : child) {
        if (v == largest) continue;
        colorSet[u]->insert(colorSet[v]->begin(), colorSet[v]->end());
    }

    colorSet[u]->insert(colors[u]);
    ans[u] = colorSet[u]->size();
}




int main(){
    int n; cin >> n;
    vector<vector<int>> adj(n, vector<int>());
    ans.resize(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        colors.push_back(x);
    }

    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> parents(n, -1);
    vector<set<int>*> colorSet(n);
    dfs(0, -1, adj, colorSet);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

}