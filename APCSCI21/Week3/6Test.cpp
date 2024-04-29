#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    int n; cin >> n;
    string s; cin >> s;
    int q; cin >> q;
    vector<set<int>> letters(26, set<int>());

    for (int i = 0; i < n; i++) {
        letters[alpha.find(s[i])].insert(i);
    }

    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int j; char c; cin >> j >> c; j--;
            letters[alpha.find(s[j])].erase(j);
            letters[alpha.find(c)].insert(j);
            s[j] = c;
        } else {
            int l, r; cin >> l >> r; l--; r--;
            int ans = 0;
            for (int i = 0; i < 26; i++) {
                if (*letters[i].lower_bound(l) <= r and letters[i].lower_bound(l) != letters[i].end()) ans++;
            }
            cout << ans << "\n";
        }
    }
}