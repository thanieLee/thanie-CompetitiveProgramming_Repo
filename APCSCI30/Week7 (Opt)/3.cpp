#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<ll> colors;
vector<vector<int>> adj;
vector<ll> ans;
vector<map<ll, ll>*> cnts;
vector<pair<ll, ll>*> tempMx;

void dfs(int u, int p) {

    int largest = -1;
    vector<int> children;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            if (largest == -1 or cnts[v]->size() > cnts[largest]->size()) {
                largest = v;
            }
            children.push_back(v);
        }
    }

    if (largest == -1) {
        cnts[u] = new map<ll, ll>;
        tempMx[u] = new pair<ll, ll>;
        tempMx[u]->first = 0;
        tempMx[u]->second = 0;
    } else {
        cnts[u] = cnts[largest];
        tempMx[u] = tempMx[largest];
    }

    for (int v : children) {
        if (v == largest) continue;

        for (auto it = cnts[v]->begin(); it != cnts[v]->end(); it++) {
            (*cnts[u])[it->first] += it->second; 
            if ((*cnts[u])[it->first] > tempMx[u]->first) {
                tempMx[u]->first = (*cnts[u])[it->first];
                tempMx[u]->second = it->first;
            } else if ((*cnts[u])[it->first] == tempMx[u]->first) {
                tempMx[u]->second += it->first;
            }
        }
    }

    (*cnts[u])[colors[u]]++;
    if ((*cnts[u])[colors[u]] > tempMx[u]->first) {
        tempMx[u]->first = (*cnts[u])[colors[u]];
        tempMx[u]->second = colors[u];
    } else if ((*cnts[u])[colors[u]] == tempMx[u]->first) {
        tempMx[u]->second += colors[u];
    }

    auto en = cnts[u]->end();
    ans[u] = tempMx[u]->second;
}

int main(){
    ll n; cin >> n;
    adj.resize(n, vector<int>()); ans.resize(n); cnts.resize(n); tempMx.resize(n);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        colors.push_back(x);
    }

    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
} 