#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<vector<vector<int>>> choices;
int n;
void gen(vector<int> cur) {
    if (cur.size() == 6) return;

    choices[cur.size()].push_back(cur);

    if (cur.size() == 0) {
        for (int i = 0; i < n; i++) {
            vector<int> next = cur;
            next.push_back(i);
            gen(next);
        }
        return;
    }

    for (int i = cur[cur.size()-1]+1; i < n; i++) {
        vector<int> next = cur;
        next.push_back(i);
        gen(next);
    }
}

int main(){
    int m; cin >> n >> m;
    vector<ll> masks;
    vector<int> same;
    for (int i = 0; i < m; i++) {
        string a; cin >> a;
        int sme; cin >> sme;
        masks.push_back(stoll(a, nullptr, 2));
        same.push_back(sme);
    }
    choices.resize(6, vector<vector<int>>());
    vector<int> test;
    gen(test);
    set<ll> cor_msks;
    for (auto arr : choices[same[0]]) {
        vector<bool> stay(n, false);
        for (int v : arr) {
            stay[v] = true;
        }
        ll msk = 0;
        for (int i = 0; i < n; i++) {
            ll cur_bit = masks[0] & (1ll<<i);
            ll opp_bit = cur_bit ^ (1ll<<i);  
            if (stay[i]) {
                msk |= cur_bit;
            } else {
                msk |= opp_bit;
            }
        }

        cor_msks.insert(msk);
    }

    for (int i = 1; i < m; i++) {
        set<ll> to_remove;
        for (ll msk : cor_msks) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if ((msk & (1ll<<j)) == (masks[i] & (1ll<<j))) cnt++;
            }
            if (cnt != same[i]) to_remove.insert(msk);
        }

        for (ll msk : to_remove) {
            cor_msks.erase(msk);
        }
    }

    cout << cor_msks.size() << endl;
}