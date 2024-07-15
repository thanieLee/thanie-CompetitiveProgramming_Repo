#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

vector<int> parent, ran, siz;

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


int main(){
    ll n, m; cin >> n >> m;
    parent.resize(n);
    ran.resize(n, 0);
    siz.resize(n, 1);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    vector<pll> bridges;
    for (int i = 0; i < m; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        bridges.push_back({a, b});
    }

    reverse(bridges.begin(), bridges.end());
    vector<ll> ans = {(n * (n-1))/2};

    for (int i = 0; i < m-1; i++) {
        pll cur = bridges[i];
        ll a = cur.first, b = cur.second;
        ll prevAns = ans[ans.size()-1];
        if (find(a) != find(b)) {
            //cout << siz[find(a)] << " " << siz[find(b)] << endl;
            prevAns -= siz[find(a)]*siz[find(b)];
            connect(a, b);
        }
        ans.push_back(prevAns);
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }
}
