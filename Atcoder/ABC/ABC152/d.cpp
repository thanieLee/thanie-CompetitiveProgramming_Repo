#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) (int)(x.size())

int main(){
    int n; cin >> n;
    vector<int> dp(n+1, -1);
    dp[1] = 0;
    string nString = to_string(n);
    for (int i = 1; i <= n; i++){
        string iString = to_string(i);
        int firstDigit = iString[0] - '0';
        int lastDigit = iString[len(iString)-1] - '0';
        if (lastDigit == 0) {
            dp[i] = dp[i-1];
            continue;
        }
        int cnt = 0;
        if (nString[0]-'0' >= lastDigit and len(nString) > 2) {
            int mid = stoi(nString.substr(1, len(nString)-2));
            cnt += mid+1;
        }

        for (int j = len(nString)-3; j > 0; j--){
            cnt += 10 * (j);
        }

        //Two digits
        if (firstDigit == lastDigit and firstDigit <= (nString[0]-'0') and len(nString) >= 2) {
            cnt++;
        } else if (len(iString) == 2 and lastDigit <= (nString[0]-'0')){
            cnt += 1;
        }

        //One digit
        if (firstDigit == lastDigit) {
            cnt++;
        }
        
        if (i == 1) {
            dp[i] = cnt;
            continue;
        }
        dp[i] = dp[i-1]+cnt;

    }
    cout << dp[n] << endl;
}