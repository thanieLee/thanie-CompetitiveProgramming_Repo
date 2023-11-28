#include <bits/stdc++.h>
using namespace std;


const int max_node = 100001;
vector<int> graph[max_node];             
vector<int> transpose_graph[max_node];   
bool vis[max_node];                      
vector<int> node_order;    
vector<vector<int>> sccs = {{}};
vector<int> scc(max_node, -1);
vector<int> sccParent(max_node, -1);
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

void dfs3(int n, int p, int &anc, int depth, vector<bool>& visited, vector<vector<int>>& sccGraph, vector<int> &in, vector<pair<int, int>> &out){
    if (visited[n]) return;
    //cout << n << " " << p << " " << anc << endl;
    if (p == -1){
        in.push_back(sccParent[n]);
    }
    visited[n] = true;
    int cnt = 0;
    for (int v : sccGraph[n]){
        if (v != p){
            cnt++;
            dfs3(v, n, anc, depth+1, visited, sccGraph, in, out);
        }
    }

    if (cnt == 0){
        out.push_back({anc, sccParent[n]});
        reach[anc].push_back(sccParent[n]);
    }
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
    int n; cin >> n;

    for (int i = 1; i <= n; i++){
        int x; cin >> x;
        graph[i].push_back(x);
        transpose_graph[x].push_back(i);
    }

    if (kosarajuSCC(n) == 1) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++){
        for (int v : graph[i]){
            if (sccParent[i] == sccParent[v]) continue;
            sccGraph[sccParent[i]].push_back(sccParent[v]);
            revGraph[sccParent[v]].push_back(sccParent[i]);
        }
    }
    
    vector<bool> visited(max_node, false);
    vector<int> in;
    vector<pair<int, int>> out;
    bool rev = false;
    for (int i = 1; i <= n; i++){
        if (!visited[i] and sccParent[i] == i and revGraph[i].size() == 0) {
            dfs3(i, -1, i, 0, visited, sccGraph, in, out);
        }
    }

    in.clear();
    for (int i = 1; i <= n; i++){
        if (revGraph[i].size() == 0){
            in.push_back(i);
        }
    }
    if (in.size() > out.size()){
        for (int i = 0; i < max_node; i++){
            visited[i] = false;
            reach[i] = {};
        }
        in.clear();


        rev = true;
        for (int i = 1; i <= n; i++){
        if (!visited[i] and sccParent[i] == i and sccGraph[i].size() == 0) {
                dfs3(i, -1, i, 0, visited, revGraph, in, out);
            }
        }
    }
    
    int cnt = 0;
    vector<pair<int, int>> ans;
    //cout << "test" << endl;

    for (int i = 0; i < in.size(); i++){
        //cout << in[i] << " ";
    }
    //cout << endl;
    
    for (int i = 0; i < in.size()-1; i++){
        int cur = in[i];
        int next = in[i+1];
        //cout << i << " " << cur << endl;
        if (reach[cur].size() == 0) continue;
        for (int j = 1; j < reach[cur].size(); j++){
            //cout << j << endl;
            ans.push_back({reach[cur][j-1], reach[cur][j]});
        }
       // cout << reach[cur].size() << endl;
        ans.push_back({reach[cur][reach[cur].size()-1], next});
    }

    int cur = in[in.size()-1];
    int next = in[0];
    if (reach[cur].size() > 0){
        for (int j = 1; j < reach[cur].size(); j++){
                ans.push_back({reach[cur][j-1], reach[cur][j]});
            }
        ans.push_back({reach[cur][reach[cur].size()-1], next});
    }

    //cout << "heehee" << endl;
    cout << ans.size() << endl;

    for (int i = 0; i < ans.size(); i++){
        if (!rev)
            cout << ans[i].first << " " << ans[i].second << endl;
        else
            cout << ans[i].second << " " << ans[i].first << endl;
    }
}