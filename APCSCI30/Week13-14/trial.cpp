#include <bits/stdc++.h>
using namespace std;
 
vector<int> z(string s, int size) {
        int n = s.size();
        vector<int> z(n);
        int x = 0, y = 0;
        for (int i = 1; i < n; i++) {
           z[i] = max(0,min(z[i-x],y-i+1));
           while (i+z[i] < n && s[z[i]] == s[i+z[i]]) {
               x = i; y = i+z[i]; z[i]++;
           }
    }
    reverse(z.begin(), z.end());
    for (int i = 0; i < size; i++){
        z.pop_back();
    }
    reverse(z.begin(), z.end());
    return z;
}

 
int main(){
    string w, p, s; cin >> w >> p >> s;

    string prefString = p + "#" + w;
    string suffString = s + "#" + w;

    vector<int> prefArr = z(prefString, p.size());
    vector<int> suffArr  = z(suffString, s.size());

    for (int i = 0; i < prefArr.size(); i++){
        cout << prefArr[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < suffArr.size(); i++){
        cout << suffArr[i] << " ";
    }
    cout << endl;
    
  
}