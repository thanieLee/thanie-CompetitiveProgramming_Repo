#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;


ll twoCnt(ll cur) {
    ll two = 0;

    while (cur % 2 == 0 and cur != 0) {
        two++;
        cur /= 2;
    }
    if (cur == 0) return 1;
    return two;
}

ll fiveCnt(ll cur) {
    ll five = 0;
    while (cur % 5 == 0 and cur != 0) {
        five++;
        cur /= 5;
    }
    if (cur == 0) return 1;
    return five;
}



int main(){
    int n; cin >> n;
    vector<vector<ll>> graph(n, vector<ll>(n));
    bool zero = false;
    pii z;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ll cur; cin >> cur;
            graph[i][j] = cur;
            if (cur == 0) {
                z = {i, j};
                zero = true;
            }
        }
    }

    vector<vector<ll>> dp2(n, vector<ll>(n, 0));
    vector<vector<ll>> dp5(n, vector<ll>(n, 0));
    dp2[0][0] = twoCnt(graph[0][0]);
    dp5[0][0] = fiveCnt(graph[0][0]);
    vector<vector<char>> dir2(n, vector<char>(n));
    vector<vector<char>> dir5(n, vector<char>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 and j == 0) continue;

            if (i == 0) {
                ll prev2 = dp2[i][j-1];
                dp2[i][j] = prev2+twoCnt(graph[i][j]);
                dir2[i][j] = 'R';

                ll prev5 = dp5[i][j-1];
                dp5[i][j] = prev5+fiveCnt(graph[i][j]);
                dir5[i][j] = 'R';

            } else if (j == 0) {
                ll prev2 = dp2[i-1][j];
                dp2[i][j] = prev2+twoCnt(graph[i][j]);
                dir2[i][j] = 'D';

                ll prev5 = dp5[i-1][j];
                dp5[i][j] = prev5+fiveCnt(graph[i][j]);
                dir5[i][j] = 'D';
            } else {
                ll prev21 = dp2[i-1][j];
                ll prev22 = dp2[i][j-1];

                ll newLL21 = prev21 + twoCnt(graph[i][j]);
                ll newLL22 = prev22 + twoCnt(graph[i][j]);

                ll prev51 = dp5[i-1][j];
                ll prev52 = dp5[i][j-1];

                ll newLL51 = prev51 + fiveCnt(graph[i][j]);
                ll newLL52 = prev52 + fiveCnt(graph[i][j]);

                if (newLL21 < newLL22) {
                    dp2[i][j] = newLL21;
                    dir2[i][j] = 'D';
                } else if (newLL21 > newLL22){
                    dp2[i][j] = newLL22;
                    dir2[i][j] = 'R';
                } else {
                    if (newLL51 < newLL52) {
                        dp2[i][j] = newLL21;
                        dir2[i][j] = 'D';
                    } else {
                        dp2[i][j] = newLL22;
                        dir2[i][j] = 'R';
                    }
                }


                if (newLL51 < newLL52) {
                    dp5[i][j] = newLL51;
                    dir5[i][j] = 'D';
                } else if (newLL51 > newLL52) {
                    dp5[i][j] = newLL52;
                    dir5[i][j] = 'R';
                } else {
                    if (newLL21 < newLL22) {
                        dp5[i][j] = newLL51;
                        dir5[i][j] = 'D';
                    } else {
                        dp5[i][j] = newLL52;
                        dir5[i][j] = 'R';
                    }   
                }
            }
        }
    }

    string ans = "";
    ll cnt;

    if (zero and min(dp2[n-1][n-1],dp5[n-1][n-1]) > 1) {
        int i = z.first;
        int j = z.second;
        string ans = "";
        for (int k = 0; k < i; k++) {
            ans.push_back('D');
        }

        for (int k = 0; k < j; k++) {
            ans.push_back('R');
        }

        for (int k = 0; k < n-i-1; k++) {
            ans.push_back('D');
        }

        for (int k = 0; k < n-j-1; k++) {
            ans.push_back('R');
        }
        cout << 1 << endl;
        cout << ans << endl;
        return 0;
    } 


    if (dp2[n-1][n-1] < dp5[n-1][n-1]) {
        cnt = dp2[n-1][n-1];
        int i = n-1, j = n-1;
        while (i > 0 or j > 0) {
            ans.push_back(dir2[i][j]);
            if (dir2[i][j] == 'D') {
                i--;
            } else {
                j--;
            }
        }
    } else {
        cnt = dp5[n-1][n-1];
        int i = n-1, j = n-1;
        while (i > 0 or j > 0) {
            ans.push_back(dir5[i][j]);
            if (dir5[i][j] == 'D') {
                i--;
            } else {
                j--;
            }
        }
    }
    reverse(ans.begin(), ans.end());

    

    cout << cnt << endl;
    cout << ans << endl;
}   