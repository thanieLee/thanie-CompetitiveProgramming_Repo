#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll INF = 10000000000;



int main(){
    int n, a, b; cin >> n >> a >> b;
    vector<int> out(n, -1);
    int cnt = n;
    int blocked = 0;
    vector<bool> done(n, false);

    if (a == n and b == 1) {
        for (int i = 1; i <= n; i++){
            cout << i << " ";
        }
        return 0;
    }

    if (a == 1 and b == n) {
        for (int i = n; i > 0; i--){
            cout << i << " ";
        }
        return 0;
    }

    if (a > n or b > n) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 1; i < a; i++) {
        cnt--;
        blocked++;
        out[n-(a-i)] = i;
        done[i-1] = true;
    }

    int highEnd = cnt;
    int lowEnd = cnt-a;
    if (b > highEnd or b < lowEnd) {
        cout << -1 << endl;
    } else {
        for (int i = n; i >= n-(b-1); i--){
            out[(n) - (blocked) - (b-1 + (n - i))] = i;
            done[i-1] = true;
        }

        int index = 0;
        for (int i  = 1; i <= n; i++){
            if (!done[i-1]) {
                out[index] = i;
                done[i-1] = true;
                index++;
            }
        }

        for (int i = 0; i < n; i++){
            if (out[i] == -1) {
                cout << out[n+1] << endl;
            }
            cout << out[i] << " ";
        }
    }
}









/*
int getInvCount(vector<int> arr, int n)
{
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                inv_count++;
 
    return inv_count;
}

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
*/