#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
int n, m;
ll MOD = 998244353;
ll first_val;

vector<vector<char>> graph;
map<ll, ll> bitmasks;
int coord_to_id(pii x) {
    return x.first*m + x.second;
}

ll mod(ll x, ll m) {
    return ((x%m)+m)%m;
}

ll mod_pow(ll x, ll y, ll p) {
    ll res = 1;
    x = mod(x, p);
    if (x == 0) return 0;
    while (y > 0) {
        if (y & 1) {
            res = mod(res*x, p);
        }

        y = y>>1;
        x = mod(x*x, p);
        res = mod(res, p);
    }
    return res;
}

pii id_to_coord(int x ) {
    return {x/m, (x%m)};
}

bool is_icpc(int id) {
    pii coord = id_to_coord(id);
    int r = coord.first;
    int c = coord.second;
    if (r == n-1 or c == m-1) return false;
    if (graph[r][c] == 'I' and graph[r][c+1] == 'C' and graph[r+1][c+1] == 'C' and graph[r+1][c] == 'P') {
        return true;
    }
    return false;
}
ll ans = 0;
void generate(ll msk, ll dep) {
    vector<vector<bool>> untouched(n, vector<bool>(m, true));
    if (bitmasks.find(msk) != bitmasks.end()) return;

    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < m-1; j++) {
            int id = coord_to_id({i, j});
            if ((msk) & (1<<id)) {
                untouched[i][j] = false;
                untouched[i+1][j] = false;
                untouched[i][j+1] = false;
                untouched[i+1][j+1] = false;
            }
        }
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < m-1; j++) {
            int id = coord_to_id({i, j});
            if (untouched[i][j] and untouched[i+1][j] and untouched[i][j+1] and untouched[i+1][j+1]) {
                if ((graph[i][j] == 'I' or graph[i][j] == '?'))
                    if ((graph[i][j+1] == 'C' or graph[i][j+1] == '?'))
                        if ((graph[i+1][j+1] == 'C' or graph[i+1][j+1] == '?'))
                            if (graph[i+1][j] == 'P' or graph[i+1][j] == '?')
                                generate(msk | (1<<id), dep+1);

            }
        }
    }

    ll total_mark = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int id = coord_to_id({i, j});
            if (untouched[i][j] and graph[i][j] == '?') {
                total_mark++;
            }
        }
    }

    if (dep > 0) {
        bitmasks[msk] = total_mark;
        if (dep % 2 == 1) {
            ans += mod_pow(3, total_mark, MOD);
            ans = mod(ans, MOD);
        } else {
            ans -= mod_pow(3, total_mark, MOD);
            ans = mod(ans, MOD);
        }
    }
    else
        first_val = total_mark;
}

int main() {
    cin >> n >> m;
    graph.resize(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            graph[i][j] = s[j];
        }
    }

    ll msk = 0;
    for (int i = 0; i < n*m; i++) {
        cout << i << endl;
        if (is_icpc(i)) msk |= (1<<i);
    }
;
    if (msk > 0) {
        ans = mod_pow(3, first_val, MOD);
        cout << ans << endl;
        return 0;
    }
    generate(msk, 0);

    cout << ans << endl;
}