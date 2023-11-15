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
  void prim(viii &res, ll s, vector<bool> &vis) {
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
    res.push_back(edge);

    for (auto &[v, w] : adj[u])
      if (!vis[v]){ pq.push({w, {u, v}});}}
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
    vector<pair<ll, ll>> coor(1, {0, 0});
    vector<vector<ll>> connect(n+1, vector<ll>(n+1, 0));
    vector<ll> build(n+1, 0);
    construct.resize(n+1, 0);

    for (int i = 0; i < n; i++){
        ll a, b; cin >> a >> b;
        coor.push_back({a, b});
    }

    for (int i = 1; i < n+1; i++){
        ll x; cin >> x;
        construct[i] = x;
    }

    for (int i = 1; i < n+1; i++){
        ll x; cin >> x;
        build[i] = x;
    }   

    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < n+1; j++){
            if (i == j) continue;
            connect[i][j] = dist(coor[i], coor[j]) * (build[i] + build[j]);
        }
    }

    graph g(n+1);
    for (int i = 1; i < n+1; i++){
        g.add_edge(0, i, construct[i]);
        for (int j = 1; j < n+1; j++){
            if (i == j) continue;
            g.add_edge(i, j, connect[i][j]);
        }
    }

    viii res;
    vector<bool> visited(n+1, false);
    vector<bool> cons(n+1, false);
    g.prim(res, 0, visited);
    sort(res.begin(), res.end(), cmp);
    vector<ll> bui;
    vector<ii> con;
    ll cnt = 0;
    for (int i = 0; i < res.size(); i++){
        if (res[i].second.first == 0){
            bui.push_back(res[i].second.second);
        }  else {
            con.push_back(res[i].second);
        }
        cnt += res[i].first;
    }
    cout << cnt << endl;
    cout << bui.size() << endl;

    for (int i = 0; i < bui.size(); i++){
        cout << bui[i] << " ";
    
    }
    cout << endl;

    cout << con.size() << endl;
    for (int i = 0; i < con.size(); i++){
        cout << con[i].first << " " << con[i].second << endl;
    }

}