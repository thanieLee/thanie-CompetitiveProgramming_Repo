#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
ld a, b, x, d;
ld total;
ld PI = 3.141592653589793238462643383279502884L;
bool cmp3(ld M) {
    ld theta = M*(PI/180);
    //cout << theta << " " << b * tan(PI/2 - theta) << " " << a << endl;
    if (x <= total/2) {
        ld opposite = b * tan(PI/2 - theta);
        return (opposite * b * a)/2 >= x;
    } else {
        ld opposite = a * tan(theta);
        return total-(opposite*a*a)/2 >= x;
    }
    
}
   
template <typename Can> ld bsearch(ld L, ld R, const Can& can) {
    while(R - L > 0.000000001l) {
        ld M = L + (R-L) / ((ld) 2l);
        //cout << L << " " << M << " " << R << endl;
        (can(M) ? L : R) = M;
    }

    return L;
}

int main() {
    cin >> a >> b >> x;
    d = sqrt(a*a + b*b);
    total = a*a*b;
    ld L = 0l, R = 90l;
    cout << fixed << setprecision(10);
    cout << bsearch(L, R, cmp3) << endl;
}