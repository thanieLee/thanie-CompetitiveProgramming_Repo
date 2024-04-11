#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
vector<vector<vector<ll>>> sudokus;

void generate(int cur, vector<vector<ll>> curSudoku){
    if (cur == 4) {
        sudokus.push_back(curSudoku);
        return;
    } else {
        vector<ll> perm = {1, 2, 3, 4};
        do {
            vector<vector<ll>> next = curSudoku;
            next.push_back(perm);
            generate(cur+1, next);
        } while (next_permutation(perm.begin(), perm.end()));
    }
}

int price(vector<vector<vector<ll>>> &fin, vector<vector<ll>> cur, int k) {
    int ans = 0;
    for (auto sud : fin) {
        int cost = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (cur[i][j] == 0) continue;
                if (cur[i][j] != sud[i][j]) cost++;
            }
        }
        if (cost <= k) ans++;
    }
    return ans;
}

int main(){
    generate(0, {});
    
    vector<vector<vector<ll>>> col, final;
    vector<vector<pll>> deltas = {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}, {{2, 0}, {2, 1}, {3, 0}, {3, 1}}, {{0, 2}, {0, 3}, {1, 2}, {1, 3}}, {{2, 2}, {2, 3}, {3, 2}, {3, 3}}};
    for (auto sud : sudokus) {
        bool can = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int l = 0; l < 4; l++) {
                    if (j == l) continue;
                    if (sud[j][i] == sud[l][i]) can = false;
                }
            }
        }

        if (can)
            col.push_back(sud);
    }

    for (auto sud : col) {
        bool can = true;
        for (auto delta : deltas) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (i == j) continue;
                    if (sud[delta[i].first][delta[i].second] == sud[delta[j].first][delta[j].second]) can = false;
                }
            }
        }
        if (can) final.push_back(sud);
    }

    int T; cin >> T;
    while (T--) {
        vector<vector<ll>> cur(4, vector<ll>(4, ' '));
        int k; cin >> k;
        for (int i = 0; i < 4; i++) {
            string row; cin >> row;
            for (int j = 0; j < 4; j++) {
                if (row[j] == '.') {
                    cur[i][j] = 0;
                } else{
                    cur[i][j] = row[j]-'0';
                }
            }
        }
        cout << price(final, cur, k) << endl;
    }
}