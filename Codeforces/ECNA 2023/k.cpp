#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int ans = 0;
multiset<pair<pair<string, string>, pair<int, int>>> pairs; 
void solve(vector<string> words){  
    for (int i = 0; i < words.size()-1; i++) {
        for (int j = i+1; j < words.size(); j++) {
            string cur = words[i], next = words[j];
            int pos_diff = 0, diff_idx = -1;
            for (int k = 0; k < cur.size()-1; k++) {
                if (cur[k] != next[k] and cur[k+1] != next[k+1]) {
                    pos_diff++;
                    diff_idx = k;
                }
            }

            if (cur[cur.size()-1] != next[next.size()-1] and diff_idx != next.size()-2) {
                pos_diff++; diff_idx = -1;
            }
            //cout << pos_diff << " " << diff_idx << endl;
            if (pos_diff == 1 and diff_idx != -1) {
                vector<string> test = {cur.substr(diff_idx, 2), next.substr(diff_idx, 2)};
                string first = test[0], second = test[1];
                pairs.insert({{first, second}, {diff_idx, words[0].size()}});
            }
        }
    }
}

int main(){
    int n; cin >> n;
    map<int, vector<string>> lengths;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (lengths.find(s.size()) == lengths.end()) {
            lengths[s.size()] = {s};
        } else {
            lengths[s.size()].push_back(s);
        }
    }

    for (auto p : lengths) {
        solve(p.second);
    }
    
    while (pairs.size() > 0) {
        pair<pair<string, string>,pair<int, int>> test = *pairs.begin();
        pairs.erase(pairs.begin());
        if (*pairs.begin() != test) {
            //cout << test.first << " " << test.second << endl;
            ans++;
        }
        pairs.erase(test);
    }

    cout << ans << endl;
}