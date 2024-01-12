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
    int ans = 1;
    for (int fa : fac) {
        vector<int> r = arr;
        for (int i = 0; i < n; i++){
            r[i] = r[i]%fa;
        }

        sort(r.begin(), r.end());
        reverse(r.begin(), r.end());
        while (r[r.size()-1] == 0) {
            r.pop_back();
        }

         if (r.size() == 0) {
            ans = max(fa, ans);
        }

         int posCnt = 0;
         int len = r.size();

         for (int i = 0; i < len; i++){
            posCnt += r[i];
        }

        int negCnt = 0;
        for (int i = 0; i < len; i++) {
            negCnt += (r[i]%fa)-fa;
            posCnt -= r[i];
            if (negCnt + posCnt == 0 and posCnt <= k) {
                ans = max(fa, ans);
                continue;
            }
        }
    }

    cout << ans << endl;
}