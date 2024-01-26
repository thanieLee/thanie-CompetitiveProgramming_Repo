#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) int((x).size())


int grundy(int ai, int ki){
    
    int aii = ai;
    if ((int)floor(aii/ki) <= 0) return 0;
    while (aii >= ki * (int)floor(aii/ki) and aii >= 0) {
      cout << aii << " " << ki * (int)floor(aii/ki) << endl;
      aii -= (int)floor(aii/ki)+1;
    }
    if (aii < 0) return 0;

    return aii;
}
int main(){
    int n; cin >> n;
    int an = 0;
    for (int i = 0; i < n; i++){
        int ai, ki; cin >> ai >> ki;
        an ^= grundy(ai, ki);
    }
 
    if (an == 0) {
        cout << "Aoki" << endl;
    } else {
        cout << "Takahashi" << endl;
    }
}