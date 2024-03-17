#include<bits/stdc++.h>
#include<complex>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;
typedef complex<ld> point;

#define len(x) int((x).size())
#define x real()
#define y imag()

#define INF 1e10;

const ld PI = acos(-1.0), EPS = 1e-7;

ld dot(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

ld dist(point a, point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

ld angle(point a, point b, point c) {
    ld smolA = dist(b, c);
    ld smolB = dist(a, c);
    ld smolC = dist(a, b);

    return (pow(smolB, 2) - pow(smolA, 2) - pow(smolC, 2))/(-2*smolA*smolC);
}


ld slope(point a, point b) {
    if (b.x < a.x)
        swap(a, b);
    if (b.x - a.x == 0)
        return -INF;
    return (b.y - a.y) / (b.x - a.x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<point> a(4);
    for (int i = 0; i < 4; i++) {
        ll tx, ty; cin >> tx >> ty;
        a[i] = point(tx, ty);
    }

    set<vector<ld>> sides;
    map<ld, int> angles;
    for (int j = 0; j < 4; j++) {
        int ti = 0, tk = 0; ld mx = 0;
        for (int i = 0; i < 4; i++) {
            for (int k = 0; k < 4; k++) {
                if (i == j or j == k or i == k)
                    continue;
                ld theta = angle(a[i], a[j], a[k]);
                if (theta > mx) {
                    mx = theta;
                    ti = i;
                    tk = k;
                }
            }
        }
        bool found = false;
        for (auto& a : angles) {
            if (abs(a.first - mx) <= 1e-5) {
                a.second++;
                found = true;
                break;
            }
        }
        if (!found)
            angles[mx]++;
        
        sides.insert({dist(a[ti], a[j]), (ld)min(ti, j), (ld)max(ti, j)});
        sides.insert({dist(a[j], a[tk]), (ld)min(tk, j), (ld)max(tk, j)});
    }
    int right = 0;
    int pairs = 0;
    map<ld, int> cnt;
    map<ld, int> slopes;

    for (auto side : sides) {
        cnt[side[0]]++;
        ld temp = slope(a[side[1]], a[side[2]]);
        bool found = false;
        for (auto s : slopes) {
            if (abs(s.first - temp) <= 1e-5) {
                found = true;
                slopes[temp]++;
                break;
            }
        }
        if (!found)
            slopes[temp]++;
        
        // cout << side[0] << " ";
    }
    // cout << endl;
    bool kite = false;
    for (auto a : angles) {
        if (abs(a.first-PI/2) <= 1e-5)
            right += a.second;
        if (a.second >= 2)
            kite = true;
        // cout << a.first << "," << a.second << " ";
    }
    // cout << endl;
    for (auto s : slopes) {
        if (s.second >= 2)
            pairs++;
        // cout << s.first << "," << s.second << " ";
    }
    
    // cout << endl;
    
    bool same = cnt.begin()->second == 4;
    cout << same << " " << right << endl;
    if (same and right == 4)
        cout << "square";
    else if (right == 4)
        cout << "rectangle";
    else if (same)
        cout << "rhombus";
    else if (pairs >= 2)
        cout << "parallelogram";
    else if (pairs == 1)
        cout << "trapezium";
    else if (kite)
        cout << "kite";
    else
        cout << "none";
    

}