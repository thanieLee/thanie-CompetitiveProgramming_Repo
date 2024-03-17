#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;


struct frac{
    int p, q;

    frac(int x, int y = 1){
        p = x;
        q = y;
        reduce();
    }

    void reduce(){
        if (p == 0) {
            q = 1;
            return;
        }
        if (q == 0) return;
        int d = gcd(p, q);
        p = p/d;
        q = q/d;
    }

    frac operator+ (frac y) {
        frac cur = *this;
        int prevq = cur.q;
        cur.q = lcm(cur.q, y.q);
        cur.p = cur.p*(cur.q/prevq) + y.p*(cur.q/y.q);
        cur.reduce();
        return cur;
    }

    frac operator- (frac y) {
        frac cur = *this;
        int prevq = cur.q;
        cur.q = lcm(cur.q, y.q);
        cur.p = cur.p*(cur.q/prevq) - y.p*(cur.q/y.q);
        cur.reduce();
        return cur;
    }

    frac operator* (frac y){
        frac cur = *this;
        cur.p = cur.p*y.p;
        cur.q = cur.q*y.q;
        cur.reduce();
        return cur;
    }

    frac operator/ (frac y){
        frac cur = *this;
        cur.p = cur.p*y.q;
        cur.q = cur.q*y.p;
        cur.reduce();
        return cur;
    }

    frac operator += (frac y){
        *this + y;
        return *this;
    }
};


struct point{
    int x, y;

    point(int x1, int y1){
        x = x1;
        y = y1;
    }

    frac slope(point b){
        return frac((this->y-b.y), (this->x)-b.x);
    }
};

int main(){
    int n; cin >> n;
    vector<point> points;

    for (int i = 0; i < n; i++){
        int xi, yi; cin >> xi >> yi;
        points.push_back(point(xi, yi));
    }
    vector<bool> valid(n, false);
    for (int i = 0; i < 3; i++){
        unordered_map<int, unordered_map<int, int>> test;
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                if (j == k) continue;
                if (valid[j] or valid[k])  
                if (test.find(points[j].slope(points[k]).p) == test.end()) {
                    test[points[j].slope(points[k]).p] = unordered_map<int, int>();
                }

                if (test[points[j].slope(points[k]).p].find(points[j].slope(points[k]).q) == test[points[j].slope(points[k]).p].end()) {
                    test[points[j].slope(points[k]).p][points[j].slope(points[k]).q] = 0;
                }
                test[points[j].slope(points[k]).p][points[j].slope(points[k]).q]++;
            }
        }
    }

    
}