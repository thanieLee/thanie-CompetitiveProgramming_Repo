#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

bool no(deque<int> a, deque<int> b) {
    bool can = true;
    int n = a.size();
    for  (int i = 0; i < n; i++) {
        if (a.front() > b.front()) {
            can = false;
        }
        a.pop_front();
        b.pop_front();
    } 

    return can;
}

int main(){
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        deque<int> a, b;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            a.push_back(ai);
        }

        for (int i = 0; i < n; i++) {
            int bi; cin >> bi;
            b.push_back(bi);
        }

        int ans = 0;
        while (not no(a, b)) {
            ans++;
            a.pop_back();
            a.push_front(0);
        }
        cout << ans << endl;
    }
}