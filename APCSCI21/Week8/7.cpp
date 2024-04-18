#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll n, k;
ll MOD = 100000007;
set<ll> valid;
vector<ll> deltax = {0, -1, 0, 1};
vector<ll> deltay = {1, 0, -1, 0};
vector<vector<char>> graph;

struct point {
    ll x, y;
    point (ll xi, ll yi) {
        x = xi;
        y = yi;
    }
};

bool isPrime(int n) 
{ 
    if (n <= 1) 
        return false; 
    for (int i = 2; i <= sqrt(n); i++) 
        if (n % i == 0) 
            return false; 
    return true; 
} 

ll mod(ll x) {
    return ((x%MOD)+MOD)%MOD;
}
vector<ll> primes;

ll ptToCor(point a) {
    return (a.x*n)+a.y;
}

point corToPt(ll cor) {
    return point(cor/n, cor%n);
}

void dfs(ll cur, ll dep, ll prod) {
    if (dep == k) {
        valid.insert(prod);
    } else {
        for (int i = 0; i < n*n; i++) {
            if (!(prod & (1ll<<i))) continue;
            point curPt = corToPt(i); 
            ll newProd = prod;
            ll newdep = dep+1;
            for (int i = 0; i < 4; i++) {
                ll newx = curPt.x+deltax[i];
                ll newy = curPt.y+deltay[i];
                if (0 <= newx and newx < n and 0 <= newy and newy < n) {
                    if (graph[newx][newy] == '#') continue;
                    point newPt(newx, newy);
                    ll newCor = ptToCor(newPt);
                    if (newProd & (1ll<<newCor)) continue;
                    dfs(newCor, newdep, newProd|(1ll<<newCor));
                }
            }
        }

    }
}


int main(){
    cin >> n >> k;
    graph.resize(n, vector<char>(n, ' '));
    ll cnt = 0;
    ll cur = 1;
    while (cnt <= 100) {
        if (isPrime(cur)) {
            primes.push_back(cur);
            cnt++;
        }
        cur++;
    }

    for (int i = 0; i < n; i++) {
        string cur; cin >> cur;
        for (int j = 0; j < n; j++) {
            graph[i][j] = cur[j];
        }
    }

    for (int i = 0; i < n*n; i++) {
        point cur = corToPt(i);
        if (graph[cur.x][cur.y] == '#') continue;
        dfs(i, 1, 1ll<<i);
    }

    ll ans = 0;
    for (auto it = valid.begin(); it != valid.end(); it++) {
        ans++;
        cout << (*it) << endl;
        for (int i = 0 ; i < n*n; i++) {
            if (!(*it & (1<<i))) continue;
            point curPt = corToPt(i);
            //cout << curPt.x << " " << curPt.y << endl;
        }
        //cout << endl;
    }
    cout << ans << endl;
}