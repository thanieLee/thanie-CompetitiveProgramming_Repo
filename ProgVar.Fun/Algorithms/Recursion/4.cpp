#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<vector<bool>> solve(vector<vector<bool>> cur, int dep, int end, int n, vector<vector<bool>> &model) {
    if (dep == end) return cur;

    vector<vector<bool>> next(cur.size()*n, vector<bool>(cur.size()*n));

    for (int i = 0; i < cur.size(); i++) {
        for (int j = 0; j < cur.size(); j++) {
            int startx = i*n;
            int starty = j*n;

            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (cur[i][j])
                        next[startx+k][starty+l] = model[k][l];
                    else
                        next[startx+k][starty+l] = false;
                }
            }
        }
    }

    return solve(next, dep+1, end, n, model);
}

int main(){
    ifstream fin("in");
    ofstream fout("out");
    int n, k; fin >> n >> k;
    vector<vector<bool>> graph(n, vector<bool>(n, true));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; fin >> c;
            if (c == '*') graph[i][j] = false;
        }
    }
    vector<vector<bool>> cur(1, vector<bool>(1, true));
    vector<vector<bool>> ans = solve(cur, 0, k, n, graph);
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans.size(); j++) {
            if (ans[i][j])
                fout << '.';
            else
                fout << '*';
        }
        fout << endl;
    }
}