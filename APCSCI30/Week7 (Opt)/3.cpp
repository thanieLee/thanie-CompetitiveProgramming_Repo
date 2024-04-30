#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<ll> colors;
vector<vector<int>> adj;
vector<ll> ans;
vector<map<ll, ll>*> cnts;

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
    } else {
        cnts[u] = cnts[largest];
    }

    for (int v : children) {
        if (v == largest) continue;

        for (auto it = cnts[v]->begin(); it != cnts[v]->end(); it++) {
            if (cnts[u]->find(it->first) != cnts[u]->end()) {
                (*cnts[u])[it->first] += it->second;
            } else {
                (*cnts[u])[it->first] = it->second;
            }
        }
    }

    if (cnts[u]->find(colors[u]) != cnts[u]->end()) {
        (*cnts[u])[colors[u]]++;
    } else {
        (*cnts[u])[colors[u]] = 1;
    }
    auto en = cnts[u]->end();
    en--;
    ll cnt = en->second;
    ll an = 0;
    while (en->second == cnt) {
        an += en->second*en->first;
        if (en == cnts[u]->begin()) break;
        en--;
    }
    
    ans[u] = an;
    
}

int main(){
    ll n; cin >> n;
    adj.resize(n, vector<int>()); ans.resize(n); cnts.resize(n);
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