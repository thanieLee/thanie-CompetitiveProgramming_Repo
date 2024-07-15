#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
vector<int> parent, ran, siz;

bool cmp(pair<ll, pll> x, pair<ll, pll> y) {
    if (x.first == y.first) {
        return x.second.second < y.second.second;
    }
    return x.first < y.first;
}

bool cmp1(pair<pii, int> x, pair<pii, int> y) {
    return x.second < y.second;
}

bool cmp2(pair<pii, pll> x, pair<pii, pll> y) {
    return x.second.first < y.second.first;
}


int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void connect(int i, int j) {
    int u = find(i);
    int v = find(j);

    if (u == v)
        return;
    if (ran[u] < ran[v]) {
        parent[u] = v;
        ran[v] += ran[u];
        siz[v] += siz[u];
    } else {
        parent[v] = u;
        ran[u] += ran[v];
        siz[u] += siz[v];
    }
}

struct segtree {
    vector<pair<ll, pll>> t;
    int n;
    segtree(vector<pair<ll, pll>> &a, int n) : n(n) {
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }

    void build(vector<pair<ll, pll>> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            pull(v);
        }
    }

    void pull(int v) {
        t[v] = min(t[v*2], t[v*2+1], cmp);
    }


    pair<ll, pll> query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return {100000, {-1, -1}};
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;

        return min(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r), cmp);
    }
};

struct segtree_single {
    vector<ll> t;
    int n;
    segtree_single(vector<ll> &a, int n) : n(n) {
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }

    void build(vector<ll> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            pull(v);
        }
    }

    void pull(int v) {
        t[v] = max(t[v*2], t[v*2+1]);
    }

    void update(int v, int tl, int tr, int pos, ll val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, val);
            else
                update(v*2+1, tm+1, tr, pos, val);
            pull(v);
        }
    }

    ll query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return -1;
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;

        return max(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};

vector<pair<ll, pll>> euler;
vector<ll> euler_dist;
vector<int> first;
vector<vector<pii>> mst;

int n;

int timer = 0;
void dfs(pii u, int p, int dep) {
    stack<pair<pii, pii>> stck;
    stck.push({u, {0, -1}});
    vector<bool> vis(n, false);
    vis[0] = true;
    while (!stck.empty())
    {
        pair<pii, pii> s = stck.top();
        int u = s.first.first;
        int dist = s.first.second;
        int dep = s.second.first;
        int p = s.second.second; 
        int child = 0;

        euler.push_back({dep, {u, timer}});
    

        if (first[u] == -1)
            first[u] = timer;
        
        timer++;
        int cnt = 0;
        for (pii v : mst[u]) {
            if (!vis[v.first] and v.first != p) {
                cnt++;
            }
        }

        for (pii v : mst[u]) {
            if (!vis[v.first] and v.first != p) {
                vis[v.first] = true;
                stck.push({v, {dep+1, u}});
                if (cnt > 0) {
                    stck.push({s.first, {dep, p}});
                    cnt--;
                }

                child++;
            }
        }

        stck.pop();
    }
}

int main(){
    int m, q; cin >> n >> m >> q;
    vector<pair<pii, int>> roads;
    first.resize(n, -1);
    mst.resize(n, vector<pii>());
    parent.resize(n);
    ran.resize(n, 0);
    siz.resize(n, 1);
    vector<map<int, int>> edges(n, map<int, int>());

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v, t; cin >> u >> v >> t; u--; v--;
        roads.push_back({{u, v}, t});
        edges[u][v] = t;
        edges[v][u] = t;
    }

    sort(roads.begin(), roads.end(), cmp1);

    for (auto cur : roads) {
        int u = cur.first.first;
        int v = cur.first.second;
        int t = cur.second;

        if (find(u) == find(v)) continue;
        else {
            connect(u, v);
            mst[u].push_back({v, t});
            mst[v].push_back({u, t});
        }
    }
    

    dfs({0, -1}, -1, 0);

    mst.clear();
    segtree euler_segtree(euler, euler.size());
    euler_dist = {-1};
    for (int i = 1; i < euler.size(); i++) {
        euler_dist.push_back(edges[euler[i].second.first][euler[i-1].second.first]);
    }
    segtree_single euler_dist_segtree(euler_dist, euler_dist.size());
    vector<pair<pii, pll>> queries;
    for (int i = 0; i < euler.size(); i++) {
        cout << euler[i].second.first+1 << " ";
    }
    cout << endl << endl;

    for (int i = 0; i < euler_dist.size(); i++) {
        cout << euler_dist[i] << " ";
    }
    cout << endl << endl;
    //cout << euler.size() << " " << euler_dist.size() << endl;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b; a--; b--;
        if (first[a] > first[b]) swap(a, b);

        pair<ll, pll> search = euler_segtree.query(1, 0, euler.size()-1, first[a], first[b]);
        //cout << a << " " << b << endl;
        cout << first[a] << " " << search.second.second << " " << first[b] << endl;
        ll first_half = euler_dist_segtree.query(1, 0, euler_dist.size()-1, first[a]+1, search.second.second-1);
        if (first[a]+1 == search.second.second) first_half = -1;
        ll second_half = euler_dist_segtree.query(1, 0, euler_dist.size()-1, search.second.second, first[b]);
        if (first[b] == search.second.second) second_half = -1;
        cout << first_half << " " << second_half << endl << endl;
        queries.push_back({{a, b}, {max(first_half, second_half), i}});
    }

    euler_dist_segtree.t.clear();
    euler_segtree.t.clear();
    sort(queries.begin(), queries.end(), cmp2);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ran[i] = 0;
        siz[i] = 1;
    }

    int road_idx = 0;
    vector<pair<int, pii>> ans;
    //cout << endl;
    for (auto que : queries) {
        if (road_idx < m) {
            while (roads[road_idx].second <= que.second.first) {
                connect(roads[road_idx].first.first, roads[road_idx].first.second);
                road_idx++;
                if (road_idx == m) break;
            }
        }

        ans.push_back({que.second.second, {que.second.first, siz[find(que.first.first)]}});
        //cout << que.second.second << " " << que.second.first << " " << siz[find(que.first.first)] << endl;
    }

    sort(ans.begin(), ans.end());

    for (int i = 0; i < q; i++) {
        cout << ans[i].second.first << " " << ans[i].second.second << endl;
    }
}