#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<vector<int>> all;
int n, k;

void generate(vector<int> cur) {
    cout << k << " " << cur.size() << endl;
    if (k == 0) return;
    if (cur.size() == k) {
        all.push_back(cur);
        return;
    } else {
        for (int i = 0; i < n; i++) {
            vector<int> newCur = cur;
            newCur.push_back(i);
            generate(newCur);
        }
    }
}

int score(vector<int> cur) {
    int ans = 0;
    for (int i = 0; i < cur.size()-n+1; i++) {
        set<int> c;
        for (int j = i; j < i+n; j++) {
            c.insert(cur[j]);
        }
        if (c.size() == n) ans++;
    }
    return ans;
}


int main(){
    int t; cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<int> a;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            for (int j = 0; j < ai; j++) {
                a.push_back(i);
            }
        }
        cout << a.size() << " " << k << endl;

        int curAns = 0;
        generate({});
        vector<vector<int>> curPerms;
        cout << all[0].size() << endl;
        for (int i = 0; i < all.size(); i++) {
            vector<int> cur = all[i];
            for (int j = 0; j < a.size(); j++) {
                cur.push_back(a[j]);
            }
            sort(cur.begin(), cur.end());
            do {
                if (curAns == score(cur)) {
                    curPerms.push_back(cur);
                } else if (curAns < score(cur)) {
                    curAns = score(cur);
                    curPerms = {cur};
                }
            } while (next_permutation(cur.begin(), cur.end()));
        }

        cout << curAns << endl;
        for (auto v : curPerms) {
            for (int i : v) {
                cout << i+1 << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}
