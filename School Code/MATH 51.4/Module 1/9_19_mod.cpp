#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int mod11(int x) {
    return ((x%11)+11)%11;
}

int main(){
    string n; cin >> n;
    if (n == "0") {
        cout << 0 << endl;
        return 0;
    }
    int l = n.size();
    int cnt = 0;
    vector<int> digCnt(10, 0);
    for (int i = 0; i < n.size(); i++){
        cnt += n[i] - '0';
        digCnt[n[i] - '0']++;
    }
    int oddCnt = ceil((float)l/2);
    vector dp(l+1, vector(11, vector<bool>(l+1, false)));
    dp[0][0][0] = true;
    vector take(l+1, vector(11, vector<bool>(l+1, false)));
    for (int i = 1; i < l+1; i++){
        for (int j = 0; j < 11; j++){
            for (int k = 0;k < oddCnt+1; k++){
                dp[i][j][k] = dp[i-1][j][k] or dp[i][j][k];
                if (k > 0) {
                    dp[i][j][k] = dp[i-1][mod11(j-(n[i-1] - '0'))][k-1] or dp[i][j][k];
                    if (dp[i-1][mod11(j-(n[i-1] - '0'))][k-1]) {
                        take[i][j][k] = true;
                    }
                }
            }
        }
    }
   vector<int> arr;
    for (int j = 1; j < 11; j++){
        if (mod11(2*j) != mod11(cnt)) {
            continue;
        }

        if (!(dp[l][j][oddCnt])) {
            continue;
        }

        int tempSum = j;
        int tempIdx = n.length();
        int tempCnt = oddCnt;

        while (min(tempSum, min(tempIdx, tempCnt)) >= 0) {
            if (take[tempIdx][tempSum][tempCnt]) {
                arr.push_back(n[tempIdx-1]-'0');
                tempCnt--;
                tempSum -= n[tempIdx-1]-'0';
                tempSum = mod11(tempSum);
            }
            tempIdx--;
        }

        goto out;

    }

out:
    if (arr.size() < oddCnt) {
        cout << -1 << endl;
        return 0;
    } 
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    vector<char> num(l, ' ');

    for (int i = 0; i < arr.size(); i++){
        num[2*i] = arr[i] + '0';
        digCnt[arr[i]]--;
    }

    int cIdx = 1;
    int counter =  0;
    while (counter+oddCnt < l){
        for (int i = 0; i < 10; i++){
            if (digCnt[i] > 0) {
                num[cIdx] = i+'0';
                cIdx += 2;
                counter++;
                digCnt[i]--;
                break;
            }
        }
    }

    for (int i = 0; i < num.size(); i++){
        cout << num[i];
    }
    cout << endl;
}