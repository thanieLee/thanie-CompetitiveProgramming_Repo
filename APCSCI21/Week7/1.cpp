#include <bits/stdc++.h>
using namespace std;


int find(int i, vector<int> &parent) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i], parent);
}

void connect(int i, int j, vector<int> &parent, vector<int> &rank) {
    int u = find(i, parent);
    int v = find(j, parent);
   
    if (u == v)
        return;
    if (rank[u] < rank[v]) {
        parent[u] = v;
        rank[v] += rank[u];
    } else {
        parent[v] = u;
        rank[u] += rank[v];
    }
}

int main(){
    int n, q; cin >> n >> q;

    vector<int> parent(n), rank(n, 0), size(n, 1);

    for (int i = 0; i < n; i++){
        parent[i] = i;
    }

    for (int i = 0; i < q; i++) {
       char t; cin >> t;
       if (t == 'M'){
            int a, b; cin >> a >> b; a--; b--;
            int cnt;
            if (find(a, parent) != find(b, parent))
                cnt = size[find(a, parent)] + size[find(b, parent)];
            else
                continue;
            connect(a, b, parent, rank);
            size[find(a, parent)] = cnt;
       } else {
            int i; cin >> i; i--;
            cout << size[find(i, parent)] << endl;
       }
    }
}