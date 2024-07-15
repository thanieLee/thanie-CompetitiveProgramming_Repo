#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;


int n, k;
vector<vector<int>> pos;
void gen(vector<int> cur) {
    if (cur.size() == 0) {
        for (int i = 0; i < n; i++) {
            vector<int> next = cur;
            next.push_back(i);
            gen(next);
        }
        return;
    }

    if (n-cur[cur.size()-1]-1 < k-cur.size()) return;

    if (cur.size() == k)  {
        pos.push_back(cur);
        return;
    }

    for (int i = cur[cur.size()-1]+1; i < n; i++) {
        vector<int> next = cur;
        next.push_back(i);
        gen(next);
    }
}

int timer = 0;
int main(){
    cin >> n >> k;
    map<string, int> hash;
    vector<int> temp;
    gen(temp);
    vector<vector<int>> tests;
    for (int i = 0; i < n; i++) {
        int t; cin >> t;
        vector<int> cur;
        for (int j = 0; j < t; j++) {
            string s; cin >> s;
            if (hash.find(s) == hash.end()) {
                hash[s] = timer;
                cur.push_back(timer);
                timer++;
            } else {
                cur.push_back(hash[s]);
            }
        }
        tests.push_back(cur);
    }
    ll ans = 0;
    for (vector<int> cur : pos) {
        vector<int> cnt(405, 0);
        int mx = 0;
        for (int i : cur) {
            vector<int> cur_test = tests[i];

            for (int s : cur_test) {
                cnt[s]++;
                mx = max(mx, cnt[s]);
            }
        }
        if (mx <= k/2) ans++;
    }
    cout << ans << endl;
}