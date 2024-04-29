#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int MAX = 2000000000;

int main(){
    int n, q; cin >> n >> q;
    vector<multiset<int, greater<int>>> kindergartens;
    multiset<int> strongest;
    for (int i = 0; i < 200000; i++) {
        pair<multiset<int, greater<int>>, int> temp;
        multiset<int, greater<int>> cur;
        kindergartens.push_back(cur);
    }
    vector<int> val;
    vector<int> curKinder;
    for (int i = 0; i < n; i++) {
        int ai, bi; cin >> ai >> bi; bi--;
        kindergartens[bi].insert(ai);
        val.push_back(ai);
        curKinder.push_back(bi);
    }

    for (int i = 0; i < 200000; i++) {
        if (kindergartens[i].begin() != kindergartens[i].end()) {
            strongest.insert(*kindergartens[i].begin());
        }
    }

    for (int i = 0; i < q; i++) {
        int ci, di; cin >> ci >> di; ci--; di--;
        int curVal = val[ci];
        int curKin = curKinder[ci];
        strongest.erase(strongest.find(*kindergartens[curKin].begin()));
        kindergartens[curKin].erase(kindergartens[curKin].find(curVal));
        
        if (kindergartens[curKin].size() != 0)
            strongest.insert(*kindergartens[curKin].begin());

        if (kindergartens[di].size() > 0)
            strongest.erase(strongest.find(*kindergartens[di].begin()));
        kindergartens[di].insert(curVal);
        if (kindergartens[di].begin() != kindergartens[di].end())
            strongest.insert(*kindergartens[di].begin());
        curKinder[ci] = di;
        cout << *strongest.begin() << endl;
    }
}