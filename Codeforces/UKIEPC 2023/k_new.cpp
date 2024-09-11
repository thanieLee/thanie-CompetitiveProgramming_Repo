#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

int main(){
    int n, m; cin >> n >> m;
    vector<int> inc, dec;


    for (int i = 0; i < m; i++) {
        int ai, bi; cin >> ai >> bi;
        if (ai < bi) {
            inc.push_back(i+1);
        } else {
            dec.push_back(i+1);
        }
    }

    cout << "YES" << endl;
    if (inc.size() > dec.size()) {
        cout << inc.size() << endl;
        for (auto i : inc) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        cout << dec.size() << endl;
        for (auto i : dec) {
            cout << i << " ";
        }
        cout << endl;
    }
    
} 