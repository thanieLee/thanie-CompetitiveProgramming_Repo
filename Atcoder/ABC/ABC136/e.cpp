#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<int> allFactors(int x) {
    vector<int> output = {1, x};
    for (int i = 2; i <= ceil(sqrt(x)); i++) {
        if (x % i == 0) {
            if ((x/i) == i) {
                output.push_back(i);
            } else {
                output.push_back(i);
                output.push_back(x/i);
            }
        }
    }
    sort(output.begin(), output.end());
    return output;
}



int main(){
    int n, k; cin >> n >> k;
    vector<int> arr;
    int cnt = 0;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        cnt += x;
        arr.push_back(x);
    }

    vector<int> fac = allFactors(cnt);
    for (int i = 0; i < fac.size(); i++){
        cout << fac[i] << " ";
    }

    int ans = 1;
    for (int fa : fac) {
        
    }
}