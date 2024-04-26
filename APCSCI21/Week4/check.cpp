
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) x.size()
typedef pair<ll, ll> pll;

int main() {
    int n; cin >> n;
    vector<string> test;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        test.push_back(s);
    }
    int ans;
    vector<string> tmp;
    sort(test.begin(), test.end());
    do {
        string cur;
        for (int i = 0; i < n; i++) {
            cur += test[i];
        }
        int cnt = 0;
        for (int i = 0; i < len(cur); i++) {
            for (int j = i+1; j < len(cur); j++) {
                if (cur[i] == 's' and cur[j] == 'h') cnt++;
            }
        }

        if (cnt > ans) {
            ans = cnt;
            tmp = {cur};
        } else if (cnt == ans) {
            tmp.push_back(cur);
        }
    } while (next_permutation(test.begin(), test.end()));

    cout << ans << endl;
    for (auto s : tmp) {
        cout << s << endl;
    }
}