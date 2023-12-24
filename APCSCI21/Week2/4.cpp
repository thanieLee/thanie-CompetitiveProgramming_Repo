#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    vector<int> arr;
    for (int i = 0; i < 1<<n; i++){
        int x; cin >> x;
        arr.push_back(x);
    }

    for (int k = 0; k < 1<<n; k++){
        for (int i = 0; i < 1<<n; i++){
            for (int j = i+1; j < 1<<n; j++){
                if (i | j <= k){
                    cout << k << " " << arr[i] << " " << arr[j] << " " << bitset<4>(i) << " " << bitset<4>(j) << endl;
                }
            }
        }
    }
}