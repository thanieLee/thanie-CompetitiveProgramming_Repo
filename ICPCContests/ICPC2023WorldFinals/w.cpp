#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;



struct frac{
    ll n, d;

    frac (ll ni, ll di) {
        n = ni;
        d = di; 
    }

    frac(){
        n = 0;
        d = 1;
    }

    frac(ll ni) {
        n = ni;
        d = 1;
    }

    frac operator+(frac const& x) {
        frac sm;
        sm.d = lcm(d, x.d);
        sm.n = n*(sm.d/d) + x.n*(sm.d/x.d);
        ll gc = gcd(sm.n, sm.d);
        sm.n /= gc;
        sm.d /= gc;
        return sm;
    }

    frac operator-(frac const& x) {
        frac sm;
        sm.d = lcm(d, x.d);
        sm.n = n*(sm.d/d) - x.n*(sm.d/x.d);
        ll gc = gcd(sm.n, sm.d);
        sm.n /= gc;
        sm.d /= gc;
        return sm;
    }

    frac operator*(frac const& x) {
        frac pr;
        pr.n = n*x.n;
        pr.d = d*x.d;
        ll gc = gcd(pr.n, pr.d);
        pr.d /= gc;
        pr.n /= gc;
        return pr;
    }

    frac operator/(frac const& x) {
        frac pr;
        pr.n = n*x.d;
        pr.d = d*x.n;
        ll gc = gcd(pr.n, pr.d);
        pr.d /= gc;
        pr.n /= gc;
        return pr;
    }

    bool operator==(frac const& x) {
        ll a = n*x.d;
        ll b = d*x.n;
        return a == b;
    }
};

typedef vector<vector<frac>> mat;
typedef vector<frac> vec;

frac det3(mat &A) {
    frac a = A[0][0];
    frac b = A[0][1];
    frac c = A[0][2]; 
    frac d = A[1][0];
    frac e = A[1][1];
    frac f = A[1][2]; 
    frac g = A[2][0];
    frac h = A[2][1];
    frac i = A[2][2]; 

    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
} 

frac det2(mat &A) {
    frac a = A[0][0];
    frac b = A[0][1];
    frac c = A[1][0]; 
    frac d = A[1][1];

    return a*d-b*c;
}

mat inv(vector<vector<frac>> &A) {
    mat transA(3, vector<frac>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            transA[i][j] = A[j][i];
        }
    }

    mat adjA(3, vector<frac>(3 ,frac()));
    frac pos(1, 1), neg(-1, 1);
    mat sign = {{pos, neg, pos},  {neg, pos, neg}, {pos, neg, pos}};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ll cnt = 0;
            mat curMat(2, vector<frac>(2));
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (i == k or j == l) continue;
                    curMat[cnt/2][cnt%2] = transA[k][l];
                    cnt++;
                }
            }

            adjA[i][j] = det2(curMat);
        }
    }

    mat ans(3, vector<frac>(3));
    frac deter = det3(A);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ans[i][j] = (sign[i][j]*adjA[i][j])/deter;
        }
    }
    return ans;
}

vec mul(mat &A, vec &v) {
    vec ans(3);
    for (int i = 0; i < 3; i++) {
        ans[i] = A[i][0]*v[0] + A[i][1]*v[1] + A[i][2]*v[2];
    }
    return ans;
}

bool same(vec &v1, vec &v2) {
    return (v1[0]==v2[0]) and (v1[1]==v2[1]) and (v1[2]==v2[2]);
}

int main(){
    
    mat rows = {{1, 3, 5}, {1, 3, 7}, {2, 1, 8}, {5, 6, 7}, {3, 1, 4}};

    vec ans;

    for (int i = 0; i < 5; i++) {
        cout << rows[i][0].n << " " << rows[i][1].n << " " << rows[i][2].n << endl;
        ll x; cin >> x;
        ans.push_back(frac(x));
    }

    mat vectors;
    for (int i = 0; i < 5; i++) {
        for (int j = i+1; j < 5; j++) {
            for (int k = j+1; k < 5; k++) {
                mat curMat;
                curMat.push_back(rows[i]);
                curMat.push_back(rows[j]);
                curMat.push_back(rows[k]);
                mat matInv = inv(curMat);
                vec vect = {ans[i], ans[j], ans[k]};
                vec an = mul(matInv, vect);
                vectors.push_back(an);
            }
        }
    }

    for (int i = 0; i < vectors.size(); i++) {
        vec cur = vectors[i];
        ll cnt = 0;
        for (int j = 0; j < vectors.size(); j++) {
            vec nex = vectors[j];
            if (cur[0]==nex[0] and cur[1]==nex[1] and cur[2]==nex[2]) {
                cnt++;
            }
        }
        if (cnt >= 3) {
            cout << cur[0].n << " " << cur[1].n << " " << cur[2].n << endl;
            return 0;
        }
    }
}