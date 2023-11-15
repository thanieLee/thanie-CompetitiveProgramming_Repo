#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> ii;
typedef pair<ll, pair<ll, ll>> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<pair<ii, ii>> viiii;

vector<ll> construct;
struct graph {
  ll n, *dist;
  vii *adj;
  graph(ll n) {
    this->n = n;
    adj = new vii[n];
    dist = new ll[n];
  }
  void add_edge(ll u, ll v, ll w) {
    adj[u].push_back({v, w});
    // adj[v].push_back({u, w});
  }
  void prim(viii &res, ll s, vector<bool> &vis, vector<ll> &cons, vector<bool> &constructed) {
  res.clear();
  std::priority_queue<iii, viii, std::greater<iii>> pq;
  vis[s] = true;
  for (auto &[v, w] : adj[s])
    if (!vis[v]) pq.push({w, {s, v}});
  while (!pq.empty()) {
    auto edge = pq.top();    pq.pop();
    ll u = edge.second.second;
    if (vis[u]) continue;
    vis[u] = true;
    if (edge.first == cons[edge.second.second]){
        cons[edge.second.second] = true;
        res.push_back(edge);
    }
    for (auto &[v, w] : adj[u])
      if (!vis[v]){
        if (w != cons[v] or (w == cons[v] and !constructed[v]))
            pq.push({w, {u, v}});}}
  }
};

ll dist(ii &x, ii &y){
    return abs(x.first-y.first) + abs(x.second-y.second);
}

bool cmp(iii &x, iii &y){
    return construct[x.second.first] < construct[y.second.first];
}
int main(){
    ll n; cin >> n;
    vector<pair<ll, ll>> coor;
    vector<vector<ll>> connect(n, vector<ll>(n, 0));
    vector<ll> build(n, 0);
    construct.resize(n, 0);

    for (int i = 0; i < n; i++){
        ll a, b; cin >> a >> b;
        coor.push_back({a, b});
    }

    for (int i = 0; i < n; i++){
        ll x; cin >> x;
        construct[i] = x;
    }

    for (int i = 0; i < n; i++){
        ll x; cin >> x;
        build[i] = x;
    }

    ll minIdx = -1;
    ll temp = 10000000000;
    for (int i = 0; i < n; i++){
        if (construct[i] < temp) {
            temp = construct[i];
            minIdx = i;
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j) continue;
            connect[i][j] = dist(coor[i], coor[j]) * (build[i] + build[j]);
        }
    }

    graph g(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j) continue;
            g.add_edge(i, j, construct[j]);
            g.add_edge(i, j, connect[i][j]);
        }
    }

    viii res;
    vector<bool> visited(n, false);
    vector<bool> cons(n, false);
    g.prim(res, minIdx, visited, construct, cons);
    sort(res.begin(), res.end(), cmp);
    set<ll> bui;
    vector<ii> con;
    ll cnt = 0;
    for (int i = 0; i < res.size(); i++){
        cout << res[i].first << " " << res[i].second.first << " " << res[i].second.second << endl;
        if (i == 0){
            bui.insert({res[i].second.first});
            cnt += build[res[i].first];
        }

        if (build[res[i].second.second] == res[i].first){
            bui.insert({res[i].second.second});
        }  else {
            con.push_back(res[i].second);
        }
        cnt += res[i].first;
    }

    cout << cnt << endl;
    cout << bui.size() << endl;
    for (auto it = bui.begin(); it != bui.end(); it++){
        cout << *it+1 << " ";
    }
    cout << endl;

    cout << con.size() << endl;

    for (int i = 0; i < con.size(); i++){
        cout << con[i].first+1 << " " << con[i].second+1 << endl;
    }


}