#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    string s; cin >> s;
    string ans;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ans.back()) {
            ans += s[i];
        }
    }

    while (ans.size() >= 4) {
        ans.pop_back();
        ans.pop_back();
    }
    cout << ans << endl;
}