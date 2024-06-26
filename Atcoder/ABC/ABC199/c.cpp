#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    string s; cin >> s;
    string fir, sec;

    fir = s.substr(0, n);
    sec = s.substr(n, n);

    bool swp = false;

    int q; cin >> q;

    for (int i = 0; i < q; i++) {
        int t, a, b; cin >> t >> a >> b; a--; b--;
        if (t == 2) {
            swap(fir, sec);
        } else {
            if (a < n and b < n) {
                char temp = fir[a];
                fir[a] = fir[b];
                fir[b] = temp;
            } else if (a < n and b >= n) {
                char temp = fir[a];
                fir[a] = sec[b-n];
                sec[b-n] = temp;
            } else {
                char temp = sec[a-n];
                sec[a-n] = sec[b-n];
                sec[b-n] = temp;
            }
        }
    }

    cout << fir << sec << endl;
}