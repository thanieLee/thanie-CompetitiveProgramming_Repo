#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;

using cd = complex<double>;
const double PI = acos(-1);

void fft(cd a[], bool inv) {
    int n = int(sizeof(a));
    if (n == 1)
        return;
    cd a0[n/2], a1[n/2];
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, inv);
    fft(a1, inv);

    double angle = 2 * PI/n * (inv ? -1 : 1);
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

ll* mult(ll a[], ll b[], ll &k) {
    cd afa[sizeof(a)], afb[sizeof(b)];
    memcpy(afa, a, sizeof(a));
    memcpy(afb, b, sizeof(b));
    int n = 1;
    while (n < (k+1000)*60+1)
        n <<= 1;
    cd fa[n], fb[n];
    for (int i = 0; i < sizeof(a); i++) {
        fa[i] = afa[i];
        fb[i] = afb[i];
    }

    cout << "hmm" << endl;
    fft(fa, false); fft(fb, false);
    cout << "hmm" << endl;
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    ll res[n];
    for (int i = 0; i < n; i++)
        res[i] = round(fa[i].real());
    return res;
}


int main(){
    ll n, b; cin >> n >> b;
    vector<pll> points;
    vector<vector<bool>> valid(b+1, vector<bool>(7, false));
    ll dis = 0;
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        if (!valid[x][y]) {
            dis++;
            points.push_back({x, y});
        }
        valid[x][y] = true;
    }
    n = points.size();
    ll c[(b+1)*60+1];
    ll d[(b+1)*60+1];
    memset(c, 0, sizeof(c));
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n; i++) {
        c[points[i].first * (60 / points[i].second)]++;
        d[(b - points[i].first)*(60 / points[i].second)]++;
    }
    cout << "hmm" << endl;
    ll* ans = mult(c, d, b);
    cout << "hmm" << endl;
    ll q; cin >> q;
    for (int i = 0; i < q; i++) {
        ll x, y; cin >> x >> y;
        if ((60*b*y)%x != 0) {
            cout << "0/1" << endl;
        } else {
            ll cnt = ans[60*b*y/x];
            ll gc = gcd(cnt, dis*dis);
            cout << cnt/gc << "/" << (dis*dis)/gc << endl;
        }
    } 
}
