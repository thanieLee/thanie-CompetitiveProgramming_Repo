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
    string s; cin >> s;

    vector<int> ans = z(s + "#" + s);
    for (int i = s.size()+2; i < ans.size(); i++){
        //cout <<i << " " << i-s.size() << " " << ans[s.size()+1] - ans[i] << endl;
        if (i-s.size()-1 == ans[s.size()+1]-ans[i]){
            cout << i-s.size()-1 << " ";
        }
    }

    cout << s.size() << endl;
}