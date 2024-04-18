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


ll ptToCor(point a) {
    return (a.x*n)+a.y;
}

point corToPt(ll cor) {
    return point(cor/n, cor%n);
}

// void dfs(ll cur, ll dep, ll prod) {
//     if (dep == k) {
//         valid.insert(prod);
//     } else {
//         for (int i = 0; i < n*n; i++) {
//             if (!(prod & (1<<i))) continue;
//             point curPt = corToPt(i); 
//             ll newProd = prod;
//             for (int i = 0; i < 4; i++) {
//                 ll newx = curPt.x+deltax[i];
//                 ll newy = curPt.y+deltay[i];
//                 if (0 <= newx and newx < n and 0 <= newy and newy < n) {
//                     if (graph[newx][newy] == '#') continue;
//                     point newPt(newx, newy);
//                     ll newCor = ptToCor(newPt);
//                     if (newProd & (1<<newCor)) continue;
//                     dfs(newCor, dep+1, newProd|(1<<newCor));
//                 }
//             }
//         }
//     }
// }


int main(){
    cin >> n >> k;
    graph.resize(n, vector<char>(n, ' '));
    ll cnt = 0;
    ll cur = 1;

    for (int i = 0; i < n; i++) {
        string cur; cin >> cur;
        for (int j = 0; j < n; j++) {
            graph[i][j] = cur[j];
        }
    }

    vector<set<ll>> lengths(k+1, set<ll>());
    for (ll i = 0; i < n*n; i++) {
        point curPt = corToPt(i);
        if (graph[curPt.x][curPt.y] == '#') continue;
        lengths[1].insert(1ll<<i);
    }

    for (int i = 2; i <= k; i++) {
        for (int j = 1; j <= (int)(i/2); j++) {
            //cout << i << " " << j << " " << i-j << endl;
            for (auto it1 = lengths[i-j].begin(); it1 != lengths[i-j].end(); it1++) {
                for (auto it2 = lengths[j].begin(); it2 != lengths[j].end(); it2++) {
                    bool canBreak = false;
                    ll cur1 = *it1;
                    ll cur2 = *it2;

                    for (ll k = 0; k < n*n; k++) {
                        if (((cur1 & (1ll<<k)) !=  0) and ((cur2 & (1ll<<k)) !=  0)) {
                            canBreak = true;
                            break;
                        }
                    }
                    if (canBreak) continue;;
                    vector<ll> cur1Pos, cur2Pos;
                    for (ll k = 0; k < n*n; k++) {
                        if ((cur1 & (1ll<<k)) != 0) {
                            cur1Pos.push_back(k);
                        }

                        if ((cur2 & (1ll<<k)) != 0) {
                            cur2Pos.push_back(k);
                        }
                    }
                    bool can = false;
                    for (ll cur1Bit : cur1Pos) {
                        for (ll cur2Bit : cur2Pos) {
                            point cur1Pt = corToPt(cur1Bit), cur2Pt = corToPt(cur2Bit);
                            for (int m = 0; m < 4; m++) {
                                ll newx = cur1Pt.x+deltax[m];
                                ll newy = cur1Pt.y+deltay[m];
                                if (0 <= newx and newx < n and 0 <= newy and newy < n) {
                                    if (graph[newx][newy] == '#') continue;
                                    if (cur2Pt.x == newx and cur2Pt.y == newy) {
                                        can = true;
                                        break;
                                    }
                                }
                            }
                            if (can) break;
                        }
                        if (can) break;
                    }

                    if (can) {
                        lengths[i].insert(cur1 | cur2);
                    }
                }
            }
        }
    }
    cout << lengths[k].size() << endl;
}