#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
vector<vector<ll>> comb;

void generate(int cur, vector<ll> &com) {
    if (cur == 6) {
        comb.push_back(com);
    } else {
        for (int i = 1; i <= 6; i++) {
            vector<ll> next = com;
            next.push_back(i);
            generate(cur+1, next);
        }
    }
}

int main(){
    vector<ll> st;
    generate(0, st);
    cout << comb[0].size() << endl;
    vector<vector<ll>> pos;
    vector<pll> Oswaps = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5},};
    for (auto com : comb) {
        vector<pll> swaps = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}};
        vector<ll> count(7, 0);
        for (int i : com) {
            count[i]++;
        }
        int temp = 0;
        for (int i : count) {
            temp = max(temp, i);
        }
        bool can = false;


        vector<ll> orig1 = com;
        int cnt = 0;
        for (auto s : Oswaps) {;
            ll temp = orig1[s.second];
            orig1[s.second] = orig1[s.first];
            orig1[s.first] = temp;
        }

        do {
            cnt++;
            vector<ll> orig2 = com;
            for (auto s : swaps) {;
                ll temp = orig2[s.second];
                orig2[s.second] = orig2[s.first];
                orig2[s.first] = temp;
            }

            vector<ll> test = {2,3,4,5,2,3};

            if (orig1 == orig2 and swaps != Oswaps) {
                for (int i = 0; i < 6; i++) {
                    cout << com[i] << " ";
                }
                cout << endl;

                for (int i = 0 ; i < 5; i++) {
                    cout << Oswaps[i].first << " " << Oswaps[i].second << " ";
                }
                cout << endl;

                for (int i = 0 ; i <  5; i++) {
                    cout << swaps[i].first << " " << swaps[i].second << " ";
                }
                cout << endl;
                cout << endl;
            }
        } while (next_permutation(swaps.begin(), swaps.end()));
        cout << cnt << endl;
    }
}