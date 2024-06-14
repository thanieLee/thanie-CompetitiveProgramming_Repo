#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;



struct segtree {
    vector<pll> t;
    int n;

    segtree(vector<pll> &a, int n) : n(n) {
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }
    void build(vector<pll> &a, int v, int tl, int tr) {
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
        t[v] = min(t[v*2], t[v*2+1]);
    }
    void update(int v, int tl, int tr, int pos, pll val) {
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
    pll query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return pll(1000000, 1000000);
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};  

struct point {
	ll next, c, d;
	point(ll v, ll c, ll d) : next(v), c(c), d(d) {

	}
};

vector<pll> arr;
vector<pll> euler;
vector<int> colors;
vector<vector<pll>> color_euler, color_euler_count;
vector<vector<point>> adj;
vector<int> depth;
vector<ll> dist;
vector<int> start, en;
int timer = 0;


void dfs1(int u, int p, ll dep, ll distan) {
    arr.push_back({dep, u});
    start[u] = arr.size()-1;
    depth[u] = dep;
	dist[u] = distan;

    for (point v : adj[u]) {
        if (v.next != p) {
			euler.push_back({euler.size(), v.d+euler[euler.size()-1].second});
			color_euler[v.c].push_back({euler.size()-1, v.d+color_euler[v.c][color_euler[v.c].size()-1].second});
			color_euler_count[v.c].push_back({euler.size()-1, 1+color_euler_count[v.c][color_euler_count[v.c].size()-1].second});
			dfs1(v.next, u, dep+1, distan+v.d);
			euler.push_back({euler.size(), -v.d+euler[euler.size()-1].second});
			color_euler[v.c].push_back({euler.size()-1, -v.d+color_euler[v.c][color_euler[v.c].size()-1].second});
			color_euler_count[v.c].push_back({euler.size()-1, -1+color_euler_count[v.c][color_euler_count[v.c].size()-1].second});
            arr.push_back({dep, u});
        }
    }
    en[u] = arr.size()-1;
}

bool cmp(pll &x, pll &y) {
	return x.first < y.first;
}

int main(){
    int n, q; cin >> n >> q;
    adj.resize(n, {});
    start.resize(n, -1);
    en.resize(n, -1); 
	euler.resize(1, {-1, 0});
    depth.resize(n, -1);
	dist.resize(n, -1);
	color_euler.resize(n, {{-1, 0}});
	colors.resize(n, -1);
	color_euler_count.resize(n, {{-1, 0}});
    for (int i = 0; i < n-1; i++) {
        ll a, b, c, d; cin >> a >> b >> c >> d; a--; b--; c--;
        adj[a].push_back({b, c, d});
        adj[b].push_back({a, c, d});
    }

    dfs1(0, -1, 0, 0);
    segtree lca(arr, arr.size());
	for (int i = 0; i < euler.size(); i++) {
		cout << euler[i].first << " " << euler[i].second << endl;
	}
	cout << endl;
	for (int i = 0; i < n-1; i++) {
		vector<pll> cur = color_euler[i];
		for (int j = 0; j < cur.size(); j++) {
			cout << cur[j].first << " " << cur[j].second << endl;
		}
		cout << endl;
	}
	for (int i = 0; i < q; i++) {
		ll x, y, u, v; cin >> x >> y >> u >> v; x--; u--; v--;
		ll fir = start[u], sec = start[v];
		if (fir > sec) swap(fir, sec);

		ll par = lca.query(1, 0, arr.size()-1, fir, sec).second;	
		ll total = dist[u]+dist[v] - 2*dist[par];
		pll search1(fir, -1), search2(sec, -1);
		auto p1 = upper_bound(color_euler[x].begin(), color_euler[x].end(), search1);
		auto p2 = upper_bound(color_euler[x].begin(), color_euler[x].end(), search2);
		p1--; p2--;
		ll color_start = p1->second;
		ll color_end = p2->second;
		ll final_dist = total - (color_end-color_start);
		auto p3 = upper_bound(color_euler_count[x].begin(), color_euler_count[x].end(), search1);
		auto p4 = upper_bound(color_euler_count[x].begin(), color_euler_count[x].end(), search2);
		p3--; p4--;
		ll cnt_start = p3->second;
		ll cnt_end = p4->second;
		cout << fir << " " << sec << endl;
		cout << total << " " << final_dist << endl;
		cout << color_start << " " << color_end << endl;
		cout << cnt_end << " " << cnt_start << endl;
		cout << final_dist + y*(cnt_end-cnt_start) << endl;
	}
}