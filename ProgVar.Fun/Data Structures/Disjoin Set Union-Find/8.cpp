#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

vector<int> parent, ran;
vector<ll> siz;
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}
ll ans = 0;
void connect(int i, int j, ll w) {
    int u = find(i);
    int v = find(j);

    if (u == v)
        return;
    if (ran[u] < ran[v]) {
        parent[u] = v;
        ran[v] += ran[u];
        ans += w * (siz[v] * siz[u]);
        cout << siz[v] << " " << siz[u] << endl;
        siz[v] += siz[u];
    } else {
        parent[v] = u;
        ran[u] += ran[v];
        ans += w * (siz[v] * siz[u]);
        siz[u] += siz[v];        
    }
}


int main(){
    int n; cin >> n;
    parent.resize(n);
    ran.resize(n, 0);
    siz.resize(n, 1);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    vector<pair<ll, pii>> bridges; 

    for (int i = 0; i < n-1; i++) {
        int u, v; ll w; cin >> u >> v >> w;
        bridges.push_back({w, {u, v}});
    }

    sort(bridges.begin(), bridges.end());

    for (int i = 0; i < n-1; i++) {
        pair<ll, pii> cur = bridges[i];
        connect(cur.second.first, cur.second.second, cur.first);
    }

    cout << ans << endl;


}