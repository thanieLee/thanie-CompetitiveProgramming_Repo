#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
long long int MOD = 1000000007;
int n;

vector<vector<int>> adj;
vector<pair<int, ll>> ans, value;
deque<int> sta;
vector<ll> fact(200001, 1);
ll mod(ll x, ll m) {
	if (m == 0)
		return 0;
	if (m < 0)
		m *= -1;
	return (x % m + m) % m;
}
 
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll g = extended_euclid(b, mod(a, b), x, y);
	ll z = x - a/b*y;
	x = y;
	y = z;
	return g;
}
 
ll mod_inv(ll a, ll m) {
	ll x, y;
	ll g = extended_euclid(a, m, x, y);
	if (g == 1 || g == -1)
		return mod(x * g, m);
	return 0;
}
 
ll mod_div(ll a, ll b, ll m) {
	a = mod(a, m);
	ll inv = mod_inv(b, m);
	return mod(inv * a, m);
}
 
ll mod_mul(ll a, ll b, ll m)
{
    ll res = 0;
    a = mod(a,m);
    while (b > 0)
    {
        if (b % 2 == 1)
            res = mod((res + a),m);
 
        a = mod((a * 2), m);
        b /= 2;
    }
 
    return mod(res, m);
}

ll choose(int n, int r, int p) {
    return mod_div(mod(fact[n], MOD), mod_mul(mod(fact[r], MOD), fact[n-r], MOD), MOD);
}

void dfs1(int u) {
    stack<int> test;
    vector<bool> visited(n, false);
    test.push(u);

    while (!test.empty()){
        int s = test.top();
        test.pop();

        if (!visited[s]) {
            sta.push_back(s);
            visited[s] = true;
        }

        for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
            if (!visited[*i])
                test.push(*i);
    }

}

void dfs2(int u, int p){

    if (u != 0) {
        pair<int, int> curVal = value[u];
        pair<int, int> prevAns = ans[p];
        prevAns.second /= curVal.second;
        prevAns.second /= choose(n-1, curVal.first, MOD);
        prevAns.first -= curVal.first;
        curVal.second *= prevAns.second;
        curVal.second *= choose(n-1, prevAns.first, MOD);
        curVal.first = n;
        ans[u] = curVal;
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs2(v, u);
        }
    }
} 
int main(){
    ll temp = 1;
    for (int i = 1; i <= 200000; i++) {
        temp *= i;
        temp = mod(temp, MOD);
        fact[i] = temp;
    }




    cin >> n;
    adj.resize(n, vector<int>());
    value.resize(n, {1, 1});
    ans.resize(n, {-1, -1});
    vector<bool> vis(n, false);
    for (int i = 0; i < n-1; i++){
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(0);
    deque<int> staCopy;
    while (!sta.empty()) {
        int cur = sta.back();
        sta.pop_back();
        for (int p : adj[cur]) {
            if (!vis[p]) {
                pair<int, ll> parentVal = value[p];
                pair<int, ll> childVal = value[cur];
                parentVal.first += childVal.first;
                parentVal.second = mod_mul(childVal.second, parentVal.second, MOD);
                parentVal.second = mod_mul(parentVal.second, choose(parentVal.first-1, childVal.first, MOD), MOD);
                value[p] = parentVal;
            }
        }
        vis[cur] = true;
    }
    for (int i = 0; i < n; i++){
        vis[i] = false;
    }
    ans[0] = value[0];
    staCopy.push_front(0);
    vis[0] = true;
    while (!staCopy.empty()) {
        int u = staCopy.front();
        staCopy.pop_front();
        if (!vis[u]) {
            int p;
            for (int v : adj[u]) {
                if (vis[v]) {
                    p = v;
                }
            }
            pair<int, ll> curVal = value[u];
            pair<int, ll> prevAns = ans[p];
            prevAns.second = mod_div(prevAns.second, curVal.second, MOD);
            prevAns.second = mod_div(prevAns.second, choose(n-1, curVal.first, MOD), MOD);
            prevAns.first -= curVal.first;
            curVal.second = mod_mul(curVal.second, prevAns.second, MOD);
            curVal.second = mod_mul(curVal.second, choose(n-1, prevAns.first, MOD), MOD);
            curVal.first = n;
            ans[u] = curVal;
            vis[u] = true;
        }

        for (auto i = adj[u].begin(); i != adj[u].end(); ++i){
            if (!vis[*i])
                staCopy.push_front(*i);
        }
    }

    for (int i = 0; i < n; i++){
        cout << ans[i].second << endl;
    }
}