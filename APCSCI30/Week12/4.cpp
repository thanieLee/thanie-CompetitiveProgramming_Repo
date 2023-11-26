#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


const int max_node = 100001;
vector<int> graph[max_node];             
vector<int> transpose_graph[max_node];   
bool vis[max_node];                      
vector<int> node_order;    
vector<vector<int>> sccs = {{}};
vector<int> scc(max_node, -1);
vector<int> sccParent(max_node, -1);
vector<ll> sccVal(max_node, 0);
vector<ll> coin;
vector<vector<int>> sccGraph(max_node, vector<int>()), revGraph(max_node, vector<int>()), reach(max_node, vector<int>());


//this function travels the whole graph and puts the nodes in a node_order
// the nodes are pushed in order of their finish time
void dfs(int n){
    if(vis[n]) return;  //if node is already visited
    int len= graph[n].size();
    vis[n]= true;
    for(int i= 0; i<len; i++){
        dfs(graph[n][i]);
    }
    node_order.push_back(n);
}
//this function traverses the transpose graph
// at each call traverses a SCC and prints each node of that SCC to std output
void dfs2(int n,int scc_count, int &parent){
    if(vis[n] == true) return;  //if node is already visited
    sccs[sccs.size()-1].push_back(n);
    scc[n]=scc_count;
    sccParent[n] = parent;
    int len= transpose_graph[n].size();
    vis[n]= true;
    for(int i= 0; i<len; i++){
        dfs2(transpose_graph[n][i],scc_count, parent);
    }
}

void dfs3(int n, int p, int &anc, int depth, vector<bool>& visited, vector<vector<int>>& sccGraph, vector<int>& top){
    if (visited[n]) return;
    visited[n] = true;
    int cnt = 0;
    for (int v : sccGraph[n]){
        if (v != p){
            cnt++;
            dfs3(v, n, anc, depth+1, visited, sccGraph, top);
        }
    }
    top.push_back(n);
}

int kosarajuSCC(int n){
    int scc_count= 0; 
    for(int i= 1; i<=n; i++){
        if(vis[i] == false){
            dfs(i);
        }
    }
    for(int i= 1; i<=n; i++){
        vis[i]= false;
    }
    for(int i= node_order.size()-1; i>= 0; i--){
        if(vis[node_order[i]] == false){
            dfs2(node_order[i],scc_count,node_order[i]);
            scc_count++;
            sccs.push_back(vector<int>{});
        }
        
    }
    node_order.clear();
    return scc_count;
}

int main(){
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++){
        ll x; cin >> x;
        coin.push_back(x);
    }

    for (int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        transpose_graph[b].push_back(a);
    }

    kosarajuSCC(n);

    for (auto sc: sccs){
        for (auto s: sc){
            sccVal[sccParent[sc[0]]] += coin[s-1];
        }
    }

    for (int i = 1; i <= n; i++){
        for (int v : graph[i]){
            if (sccParent[i] == sccParent[v]) continue;
            sccGraph[sccParent[i]].push_back(sccParent[v]);
            revGraph[sccParent[v]].push_back(sccParent[i]);
        }
    }

    vector<int> topo;
    vector<bool> visited(max_node, false);
    for (int i = 1; i <= n; i++){
        if (!visited[i] and sccParent[i] == i){
            dfs3(i, -1, i, 0, visited, sccGraph, topo);
        }
    }

    reverse(topo.begin(), topo.end());

    vector<ll> dp(max_node, 0);

    for (int i = 0; i < topo.size(); i++){
        int cur = topo[i];
        if (revGraph[cur].size() == 0){
            dp[cur] = sccVal[cur];
        }

        for (auto next : sccGraph[cur]){
            dp[next] = max(dp[next], dp[cur]+sccVal[next]);
        }
    }

    ll ans = 0;

    for (int i = 1; i <= n; i++){
        ans = max(ans, dp[sccParent[i]]);
    }

    cout << ans << endl;


}