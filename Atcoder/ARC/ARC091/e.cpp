#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll INF = 10000000000;
int main(){
    int n, a, b; cin >> n >> a >> b;
    vector<int> arr;
    for (int i = 1; i <= n; i++){
        arr.push_back(i);
    }
    do{
        vector<ll> dp(1, INF);
        
        for (int i = 0; i < arr.size(); i++){
            cout << arr[i] << " ";
        }
        cout << ":";
        for (int i = 0; i < n; i++){
            dp.push_back(INF);
            ll cur = arr[i];
            auto it = lower_bound(dp.begin(), dp.end(), cur);
            dp[it - dp.begin()] = cur;
        }
        int temp1, temp2;
        for (int i = n; i > -1; i--){
            if (dp[i] != INF){
                cout << i+1 << " ";
                temp1 = i+1;
                break;
            }
        }

        reverse(arr.begin(), arr.end());
        dp.clear();
        dp.resize(1, INF);

        for (int i = 0; i < n; i++){
            dp.push_back(INF);
            ll cur = arr[i];
            auto it = lower_bound(dp.begin(), dp.end(), cur);
            dp[it - dp.begin()] = cur;
        }
        
        for (int i = n; i > -1; i--){
            if (dp[i] != INF){
                cout << i+1 << " ";
                temp2 = i+1;
                break;
            }
        }
        cout << temp1 + temp2 << "l" << endl;
        reverse(arr.begin(), arr.end());
    } while(next_permutation(arr.begin(), arr.end()));

}