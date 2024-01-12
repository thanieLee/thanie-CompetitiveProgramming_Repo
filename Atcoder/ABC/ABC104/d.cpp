#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int MOD = 1000000007;
int main(){
    string s; cin >> s;
    int validA = 0, validB = 0, validC = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'A') {
            validA += 1;
            validA %= MOD;
        } else if (s[i] == 'B') {
            validB += validA;
            validB %= MOD;
        } else if (s[i] == 'C') {
            validC += validB;
            validC %= MOD;
        } else {
            validC += validB;
            validC %= MOD;
            validB += validA;
            validB %= MOD;
            validA += 1;
            validA %= MOD;
            int test = validA;
            for (int i = 0; i < 2; i++){
                validA += test;
                validA %= MOD;
            }
        }
        cout << validA << " " << validB << " " << validC << endl;
    }
    
    cout << validC << endl;
}