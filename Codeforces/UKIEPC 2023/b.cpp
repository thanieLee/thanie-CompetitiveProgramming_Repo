#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n, m, k; cin >> n >> m >> k;
    vector<bool> finished(m, true);
    vector<int> start_at(m, -1);
    vector<int> price(m, 0);

    for (int i = 0; i < k; i++) {
        int pi, ci; cin >> pi >> ci; pi--; ci--;
        //cout << finished[0] << " " << start_at[0] << " " << price[0] << endl;
        if (start_at[ci] != -1) {
            if (start_at[ci] == pi) {
                price[ci] += 100;
            } else {
                price[ci] += abs(start_at[ci] - pi);
            }
            finished[ci] = true;
            start_at[ci] = -1;
        } else {
            start_at[ci] = pi;
            finished[ci] = false;
        }
    }
    //cout << finished[0] << " " << start_at[0] << " " << price[0] << endl;
    for (int i = 0; i < m; i++) {
        if (!finished[i]) {
            price[i] += 100;
        }
        cout << price[i] << " ";
    }
    cout << endl;
}