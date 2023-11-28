#include <bits/stdc++.h>
using namespace std;


const int max_node = 100001;
vector<int> graph[max_node];             
vector<int> transpose_graph[max_node];   
bool vis[max_node];                      
vector<int> node_order;    
vector<vector<int>> sccs = {{}};
map<int,int> scc;

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
void dfs2(int n,int scc_count){
    if(vis[n] == true) return;  //if node is already visited
    sccs[sccs.size()-1].push_back(n);
    scc[n]=scc_count;
    int len= transpose_graph[n].size();
    vis[n]= true;
    for(int i= 0; i<len; i++){
        dfs2(transpose_graph[n][i],scc_count);
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
            dfs2(node_order[i],scc_count);
            scc_count++;
            sccs.push_back(vector<int>{});
        }
        
    }
    node_order.clear();
    return scc_count;
}

int main(){
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        transpose_graph[b].push_back(a);
    }
    cout << kosarajuSCC(n) << endl;
    int cnt = 0;
    vector<int> ans(n+1);
    for (auto sc: sccs){
        cnt++;
        for (int c : sc){
            ans[c] = cnt;
        }
    }

    for (int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
}