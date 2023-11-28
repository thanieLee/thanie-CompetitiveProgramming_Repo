#include <bits/stdc++.h>
using namespace std;
 
vector<int> z(string s) {
        int n = s.size();
        vector<int> z(n);
        int x = 0, y = 0;
        for (int i = 1; i < n; i++) {
           z[i] = max(0,min(z[i-x],y-i+1));
           while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
               x = i; y = i+z[i]; z[i]++;
           }
    }
    return z;
}
 
int main(){
    string s, p; cin >> s >> p;
    
    vector<int> ans = z(p + "#" + s);
    int cnt = 0;
    for (int i = 0; i < ans.size(); i++){
        if (ans[i] == p.size()){
            cnt++;
        }
    }
    cout << cnt << endl;
}