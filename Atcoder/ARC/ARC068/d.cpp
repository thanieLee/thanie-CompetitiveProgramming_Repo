#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) (int)(x.size())
#define printArr(arr) for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";

int main(){
    int n; cin >> n;
    vector<int> a;
    vector<int> cnt(100001, 0);
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        cnt[x]++;
        a.push_back(x);
    }
    
    int tmp = 0;
    for (int i = 1; i < 100001; i++) {
        if (cnt[i] >= 1) {
            tmp += cnt[i]-1;
        }
    }

    cout << n - (tmp + (1 ? tmp % 2 == 1 : 0)) << endl;

}
