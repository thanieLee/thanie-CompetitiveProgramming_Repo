#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


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

struct query{
    ll x, y, w;
};

bool cmp(query &x, query &y){
    return x.w < y.w;
}


int main(){
    ll n; cin >> n;

    vector<ll> parent(n), rank(n, 0), size(n, 1);
    vector<query> q;
    for (ll i = 0; i < n; i++){
        parent[i] = i;
    }

    for (ll i = 0; i < n-1; i++) {
        ll x, y, w; cin >> x >> y >> w;
        x--; y--;
        query q1;
        q1.x = x;
        q1.y = y;
        q1.w = w;
        q.push_back(q1);
    }

    sort(q.begin(), q.end(), cmp);
    ll cnt = 0;
    for (auto cur : q){
        cnt += cur.w * (size[find(cur.x, parent)] * size[find(cur.y, parent)]);
        ll c = size[find(cur.x, parent)] + size[find(cur.y, parent)];
        connect(cur.x, cur.y, parent, rank);
        size[find(cur.x, parent)] = c;
    }

    cout << cnt << endl;

}
