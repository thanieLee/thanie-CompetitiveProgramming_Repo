#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<vector<int>> solve(vector<vector<int>> order, int dep, int end) {
    if (dep == end) return order;
    vector<vector<int>> next(dep*2, vector<int>(dep*2));

    vector<vector<int>> first(order.size(), vector<int>(order.size()));
    for (int i = 0; i < dep; i++) {
        for (int j = 0; j < dep; j++) {
            first[i][j] = order[j][i];
        }
    }

    vector<vector<int>> second = order;
    vector<vector<int>> third(order.size(), vector<int>(order.size()));

    for (int i = 0; i < dep; i++) {
        for (int j = 0; j < dep; j++) {
              third[i][j] = order[]  
        }
    }
}

int main(){
    int n, m; cin >> n >> m;

    if (n == 1) {
        cout << 1 << " " << 1 << endl;
        return;
    }

    vector<vector<int>> order = {{1, 4}, {2, 3}};

}