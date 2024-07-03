#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    string s; cin >> s;
    int k; cin >> k;

    sort(s.begin(), s.end());
    

    int cnt = 1;

    while (cnt < k) {
        next_permutation(s.begin(), s.end());
        cnt++;
    }

    cout << s << endl;
} 