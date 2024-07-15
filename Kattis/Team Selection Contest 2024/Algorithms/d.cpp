#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

int node(int x, int y) {
    x += 121;
    y += 121;

    return (x*121) + y;
}



int main(){
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        int s; cin >> s;
        int x = 0, y = 0;
        vector<vector<int>> adj(1000000, vector<int>());
        int prev_node = node(0, 0);
        int cur_node = node(0, 0);
        for (int j = 0; j < s; j++) {
            char c; cin >> c;
            if (c == 'N') y++;
            else if (c == 'S') y--;
            else if (c == 'E') x++;
            else x--;
            cur_node = node(x, y);
            adj[cur_node].push_back(prev_node);
            adj[prev_node].push_back(cur_node);
            prev_node = cur_node;
        }
        
        int ans_node = cur_node;
        deque<pair<int, int>> bfs = {{node(0, 0), 0}};
        vector<int> dist(1000000, -1);

        while (!bfs.empty()) {
            pair<int, int> cur = bfs.front();
            bfs.pop_front();
            dist[cur.first] = cur.second;
            for (int v : adj[cur.first]) {
                if (dist[v] == -1) {
                    bfs.push_back({v, cur.second+1});
                }
            }
        }

        cout << dist[ans_node] << endl;
    }
}