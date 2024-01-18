#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int mod11(int x) {
    return ((x%11)+11)%11;
}

int main(){
    string n; cin >> n; 
    int l = n.size();
    int cnt = 0;
    vector<int> digCnt(10, 0);
    for (int i = 0; i < n.size(); i++){
        cnt += n[i] - '0';
        digCnt[n[i] - '0']++;
    }
    int oddCnt = ceil((float)l/2);
    vector dp(l+1, vector(11, vector(l+1, vector<bool>(2, false))));
    dp[0][0][0][0] = true;
    vector take(l+1, vector(11, vector(l+1, vector<bool>(2, false))));
    for (int i = 1; i < l+1; i++){
        for (int j = 0; j < 11; j++){
            for (int k = 0; k < oddCnt+1; k++){
                dp[i][j][k][0] = dp[i-1][j][k][0] or dp[i][j][k][0];
                dp[i][j][k][1] = dp[i-1][j][k][1] or dp[i][j][k][1];
                if (k > 0) {
                    if (n[i-1] == '0'){
                        dp[i][j][k][0] = dp[i-1][j][k-1][0] or dp[i][j][k][0];
                        dp[i][j][k][1] = dp[i-1][j][k-1][1] or dp[i][j][k][1];

                        if (dp[i-1][j][k-1][1]) {
                            take[i][j][k][1] = true;
                        }
                        if (dp[i-1][j][k-1][0]) {
                            take[i][j][k][0] = true;
                        }
                    } else {
                        dp[i][j][k][1] = dp[i-1][mod11(j-(n[i-1] - '0'))][k-1][0] or dp[i][j][k][0];
                        dp[i][j][k][1] = dp[i-1][mod11(j-(n[i-1] - '0'))][k-1][1] or dp[i][j][k][1];
                        if (dp[i-1][mod11(j-(n[i-1] - '0'))][k-1][1]) {
                            take[i][j][k][1] = true;
                        }
                        if (dp[i-1][mod11(j-(n[i-1] - '0'))][k-1][0]) {
                            take[i][j][k][1] = true;
                        }
                    }
                }
            }
        }
    }
    vector<int> arr;
    for (int j = 0; j < 11; j++){
        if (mod11(2*j) != mod11(cnt)) {
            continue;
        }

        if (!(dp[l][j][oddCnt][1])) {
            continue;
        }
        int tempSum = j;
        int tempIdx = n.length();
        int tempCnt = oddCnt;
        int hasVal = false;
        while (min(tempSum, min(tempIdx, tempCnt)) >= 0) {
            if ((take[tempIdx][tempSum][tempCnt][1]) or (take[tempIdx][tempSum][tempCnt][0] and hasVal)) {
                arr.push_back(n[tempIdx-1]-'0');
                tempCnt--;
                tempSum -= n[tempIdx-1]-'0';
                tempSum = mod11(tempSum);
                if (n[tempIdx-1] != '0')
                    hasVal = true;
            } 
            tempIdx--;
        }
        goto out;

    }

out:
    int m = 0;;
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