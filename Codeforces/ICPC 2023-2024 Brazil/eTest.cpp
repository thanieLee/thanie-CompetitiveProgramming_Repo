#include <bits/stdc++.h>
using namespace std;

int main(){
    int mx = 0;
    vector<int> val(1e6+1, 0);
    for (int i = 0; i <= 1e6; i++){
        int sub = 0;
        for (char c : to_string(i)){
            sub += c-'0';
        }
        val[i] = i-sub;
    }

    for (int i = 0; i <= 1e6; i++){
        if (i % 9 != 0) continue;
        int cur = i;
        int cnt = 0;
        while (cur != 0) {
            cnt++;
            cur = val[cur];
        }
        mx = max(mx, cnt);
        cout << cnt << endl;
    }

    cout << mx << endl;
}