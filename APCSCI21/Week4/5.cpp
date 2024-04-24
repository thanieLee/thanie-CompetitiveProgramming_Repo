#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define len(x) x.size()

struct three {
    ll s, h, noise;
    three(ll a, ll b, ll c) {
        s = a;
        h = b;
        noise = c;
    }
};

bool cmp(three &x, three &y) {
    if (x.h == 0) {
        return true;
    }

    if (y.h == 0) {
        return false;
    }

    if (x.s == 0) {
        return false;
    }

    if (y.s == 0) {
        return true;
    }

    return x.noise > y.noise;
} 

int main() {
    ll n; cin >> n;
    vector<three> arr;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        ll sCnt = 0, hCnt = 0, noise = 0;
        for (int j = 0; j < len(s); j++) {
            if (s[j] == 's') {
                sCnt++;
            } else {
                hCnt++;
                noise += sCnt;
            }
        }
        arr.push_back({sCnt, hCnt, noise});
    }

    sort(arr.begin(), arr.end(), cmp);
    ll sCnt=0, ans=0;
    for (auto t : arr) {
        //cout << t.s << " " << t.h << " " << t.noise << endl;
        ans += t.h*sCnt;
        sCnt += t.s;
        ans += t.noise;
    }
    cout << ans << endl;
}