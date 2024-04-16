#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
vector<int> dist;

void dfs(vector<vector<int>> &adj) {
    
}

int main(){
    int n, w, h; cin >> n >> w >> h;
    vector<int> dp(n+1, -1);
    vector<pll> arr = {};
    for (int i = 0; i < n; i++) {
        int wi, hi; cin >> wi >> hi;
        arr.push_back({wi, hi});
    }

    vector<vector<int>> adj(n+2, vector<int>()), revAdj(n+2, vector<int>());
    dist.resize(n+2, 0);

    for (int i = 0; i < n; i++) {
        pll cur = arr[i];
        if (cur.first > w and cur.second > h) {
            adj[0].push_back(i+1);
            revAdj[i+1].push_back(0);
        }
        adj[i+1].push_back(n+1);
        revAdj[n+1].push_back(i+1);
    }

    for (int i = 1; i <= n; i++) {
        pll cur = arr[i-1];
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            pll next = arr[j-1];
            if (cur.first < next.first and cur.second < next.second) {
                adj[i].push_back(j);
                revAdj[j].push_back(i);
            }
        }
    }


    
}
