#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

bool enough(vector<int> &hp, ll &x, int &a, int &b){
    ll cnt = 0;

    for (int h : hp){
        cnt += max((ll)(ceil((double) (h - x*b)/(a-b))), 0ll);
    }

    return cnt <= x;
}

int main(){
    int n, a, b; cin >> n >> a >> b;
    vector<int> hp;

    for (int i = 0; i < n; i++){
        int h; cin >> h;
        hp.push_back(h);
    }

    ll low = 1;
    ll high = 10000000000;

    int check = 0;
    while (check < 1000) {
        ll mid = (low+high)/2;
        bool can = enough(hp, mid, a, b);
        if (can) {
            high = mid;
        } else {
            low = mid;
        }
        check++;
    }

    if (enough(hp, low, a, b)) {
        cout << low << endl;
    } else {
        cout << high << endl;
    }
}