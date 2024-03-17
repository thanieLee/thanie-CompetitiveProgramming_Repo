#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
using cd = complex<long double>;
const long double PI = acos(-1);

void fft(vector<cd> &a, bool inv) {
    int n = a.size();
    if (n == 1)
        return;
    
    vector<cd> a0(n/2), a1(n/2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, inv);
    fft(a1, inv);

    long double angle = 2 * PI/n * (inv ? -1 : 1);
    cd w(1), wn(cos(angle), sin(angle));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        if (inv) {
            a[i] /= 2;
            a[i+n/2] /= 2;
        }
        w *= wn;
    }
}

vector<ll> mult(vector<ll> const &a, vector<ll> const &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;

    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> res(n);
    for (int i = 0; i < n; i++)
        res[i] = round(fa[i].real());
    return res;
}

int main(){
    int t, c, o, d, i; cin >> t >> c >> o >> d >> i;
    vector<int> die = {t,c,o,d,i};
    vector<int> dieVal = {4, 6, 8, 12, 20};

    vector<ll> ans = {-1};

    for (int i = 0; i < 5; i++){
        vector<ll> cur(dieVal[i]+1, 1);
        cur[0] = 0;

        for (int j = 0; j < die[i]; j++) {
            if (ans[0] == -1) {
                ans = cur;
            } else {
                ans = mult(ans, cur);
                vector<ll> newAns(min(512, (int)ans.size()), 0);
                for (int i = 0; i < min(512, (int)ans.size()); i++){
                    newAns[i] = ans[i];
                }
                ans = newAns;
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < ans.size(); i++){
        cout << i << " " << ans[i] << endl;
        cnt += ans[i];
    }
    cout << cnt;


}