#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<string> words;
    multiset<pair<string, string>> clues;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (find(words.begin(), words.end(), s) == words.end())
            words.push_back(s);

    }
    n = words.size();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (words[i].size() != words[j].size()) continue;
            int diff_idx = -1, diff_cnt = 0;
            int len = words[i].size();
            vector<bool> check(len, true);
            int cnt = 0;
            for (int k = 0; k < len; k++) {
                if (words[i][k] != words[j][k]) {
                    check[k] = false;
                    if (diff_idx == -1) diff_idx = k;
                } else {
                    cnt++;
                }
            }

            if (cnt == len-2) {
                if (check[diff_idx] != check[diff_idx+1]) continue;
                string clue1 = "", clue2 = "";
                for (int k = 0; k < len; k++) {
                    clue1 += "_";
                    clue2 += "_";
                }

                clue1[diff_idx] = words[i][diff_idx];
                clue2[diff_idx] = words[j][diff_idx];
                clue1[diff_idx+1] = words[i][diff_idx+1];
                clue2[diff_idx+1] = words[j][diff_idx+1];

                if (clue1 > clue2) {
                    swap(clue1, clue2);
                }

                clues.insert({clue1, clue2});
            }
        }
    }
    int ans = 0;
    while (clues.size() > 0) {
        pair<string, string> top = *clues.begin();
        clues.erase(clues.begin());
        if (top != *clues.begin()) {
            cout << top.first << " " << top.second << endl;
            ans++;
        }

        clues.erase(top);
    }
    cout << ans << endl;
    return 0;
}