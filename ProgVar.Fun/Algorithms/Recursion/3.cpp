#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


int main(){
    int n; cin >> n;

    vector<int> ans = {0, 1};
    for (int i = 1; i < n; i++) {
        vector<int> rev = ans;
        reverse(ans.begin(), ans.end());
        for (int j = 0; j < rev.size(); j++) {
            rev[j] |= (1<<i);
            ans.push_back(rev[j]);
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        int cur = ans[i];
        vector<char> out(n, '0');
        for (int j = 0; j < n; j++) {
            if (cur & (1<<j)) {
                out[n-j-1] = '1';
            }
        }
        for (char c : out)
            cout << c;
        cout << endl;
    }
}