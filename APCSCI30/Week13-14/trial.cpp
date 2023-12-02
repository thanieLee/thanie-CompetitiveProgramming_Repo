#include <bits/stdc++.h>
using namespace std;


 
int main(){
    int t; cin >> t;
    while (t){
        label:
        t--;
        if (t == -1) break;
        int n; cin >> n;
        vector<vector<int>> M(n, vector<int>(n));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                int x; cin >> x;
                M[i][j] = x;
            }
        }

        vector<int> ans(n, (1<<30)-1);
        
        for (int i = 0; i < n; i++){
            for (int j = i+1; j < n; j++){
                for (int k = 0; k < 30; k++){
                    if ((M[i][j] & (1<<k)) == 0) {
                        ans[i] = ans[i] & ~(1<<k);
                        ans[j] = ans[j] & ~(1<<k);
                    }
                }
            }
        }

        vector<vector<int>> newM(n, vector<int>(n));
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (i == j) continue;
                newM[i][j] = ans[i]|ans[j];
            }
        }

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (M[i][j] != newM[i][j]){
                    cout << "NO" << endl;
                    goto label;
                }
            }
        }

        cout << "YES" << endl;
        for (int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}