#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) int((x).size())
 
bool willWin(vector<int> remainingA, vector<int> &k){
    int mx = 0;
    for (int i = 0; i < len(remainingA); i++){
        mx = max((int)floor(remainingA[i]/k[i]), mx);
    }

    if (mx == 0) {
        return false;
    }


    for (int i = 0; i < len(remainingA); i++){
        if ((int)floor(remainingA[i]/k[i]) <= 0) continue;
        for (int j = 1; j <= floor(remainingA[i]/k[i]); j++){
            vector<int> copyA = remainingA;
            copyA[i] -= j;
            if (not willWin(copyA, k))
                return true;
        }
    }

    return false;
}


int main(){
    int n; cin >> n;
    vector<int> a(n), k(n);
    
    for (int i = 0; i < n; i++){
        int ai, ki; cin >> ai >> ki;
        a[i] = ai;
        k[i] = ki;
    }

    for (int i = 0; i < len(a); i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << willWin(a, k) << endl;


}