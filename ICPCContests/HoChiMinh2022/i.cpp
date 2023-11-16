#include <bits/stdc++.h> 
using namespace std;

int main(){
    int n; cin >> n;
    vector<int> queries;

    for (int i = 0; i < n; i++){
        cout << "? " << 1 << " " << i+1 << endl;
        cout.flush();
        int x; cin >> x;
        queries.push_back(x);
    }

    vector<bool> vis(n, false);
    vector<int> ans(n, 0);

    int temp = 0;

    for (int i = 1; i < n; i++){
        if (queries[0] > queries[i]){
            temp++;
        }
    }
    vis[temp] = true;
    ans[0] = temp;

    for (int i = n-1; i >= 1; i--){
        int prod = 1;
        if (queries[i] < queries[0]){
            prod = -1;
        }

        int cnt = ((abs(queries[i]-queries[0])+1)/2);
        int cur = 0;
        int idx = ans[0];
        while (cur <= cnt){
            idx += prod;
            if (!vis[idx]){
                cur++;
                if (cur == cnt){
                    while (vis[idx]){
                        idx += prod;
                    }
                    break;
                }
            }
        }
        vis[idx] = true;
        ans[i] = idx;
    }

    cout << "! ";
    for (int i = 0; i < n; i++){
        cout << ans[i]+1 << " ";
    }
    cout << endl;
}