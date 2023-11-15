#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> ii;
typedef pair<ll, pair<ll, ll>> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<pair<ii, ii>> viiii;

ll find(ll i, vector<ll> &parent) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i], parent);
}

void connect(ll i, ll j, vector<ll> &parent, vector<ll> &rank) {
    ll u = find(i, parent);
    ll v = find(j, parent);
   
    if (u == v)
        return;
    if (rank[u] < rank[v]) {
        parent[u] = v;
        rank[v] += rank[u];
    } else {
        parent[v] = u;
        rank[u] += rank[v];
    }
}
struct path{
    ll u, v, w;
};

bool cmp(path &x, path &y){
    return x.w < y.w;
}
int main(){
    ll n, m, k; cin >> n >> m >> k;
    vector<ll> special(k);
    vector<ll> parent(n), rank(n, 0), size(n, 0);
    vector<bool> isSpecial(n, false);
    for (int i = 0; i < n; i++){
        parent[i] = i;
    }

    for (int i = 0; i < k; i++){
        ll x; cin >> x; x--;
        isSpecial[x] = true;
        size[x] = 1;
    }

    vector<path> paths;
    for (int i = 0; i < m; i++){
        ll u, v, w; cin >> u >> v >> w; u--; v--;
        path p;
        p.u = u;
        p.v = v;
        p.w = w;
        paths.push_back(p);
    }

    sort(paths.begin(), paths.end(), cmp);
    path cur = paths[0];
    ll idx = 1;
    ll prevDist = cur.w;
    ll cnt;
    if (cur.u != cur.v) {
        cnt = size[find(cur.u, parent)]+size[find(cur.v, parent)];
        connect(cur.u, cur.v, parent, rank);
        size[find(cur.u, parent)] = cnt;
    }

    while (size[find(cur.u, parent)] < k){
        cur = paths[idx];
        idx++;

        if (cur.u == cur.v) {
            prevDist = cur.w;
            continue;
        }

        if (find(cur.u, parent) == find(cur.v, parent)) continue;
        cnt = size[find(cur.u, parent)]+size[find(cur.v, parent)];
        connect(cur.u, cur.v, parent, rank);
        size[find(cur.u, parent)] = cnt;
        prevDist = cur.w;
    }

    for (int i = 0; i < k; i++){
        cout << prevDist << " ";
    }
    cout << endl;
}