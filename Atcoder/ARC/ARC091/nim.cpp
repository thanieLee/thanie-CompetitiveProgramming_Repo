#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) int((x).size())

int main(){
    int t; cin >> t;
    while (t--){
        int n; cin >> n;
        int test = 0;

        for (int i = 0; i < n; i++){
            int ai; cin >> ai;
            test ^= ai;
        }

        if (test == 0){
            cout << "second" << endl;
        } else {
            cout << "first" << endl;
        }

    }
    
    
}