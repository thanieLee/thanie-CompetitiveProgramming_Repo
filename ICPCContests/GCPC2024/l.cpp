#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<int> z; // z[i] = lcp(s, s[i:])
void computeZ(string s) {
  int n = s.length(), L = 0, R = 0; z[0] = n;
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
      while (R < n && s[R - L] == s[R]) R++;
      z[i] = R - L; R--;
    } else {
      int k = i - L;
      if (z[k] < R - i + 1) z[i] = z[k];
      else {
        L = i;
        while (R < n && s[R - L] == s[R]) R++;
        z[i] = R - L; R--; } } } }

int main(){
    string s; cin >> s;
    string newS = s+s;
    z.resize(newS.size()+1);
    computeZ(newS);
    int cnt = 0;
    for (int i = 0; i < s.size(); i++){
        if (s[i] == '('){
            cnt++;
        } else {
            cnt--;
        }

        if (cnt == 0) {
            if (z[s.size()-i-1] <= s.size()) {
                for (int j = i+1; j < s.size(); j++){
                    cout << s[j];
                }
                for (int j = 0; j <= i; j++){
                    cout << s[j];
                }
                return 0;
            }
        }
    }

    cout << "no" << endl;
    return 0;
}