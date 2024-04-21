#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll MOD = 1000000007;
ll mod(ll x){
    return ((x%MOD)+MOD)%MOD;
}

struct Matrix {
    vector<vector<ll>> a;
    ll n;

    Matrix(ll H) {
        n = H;
        for(int i = 0; i < n; i++) {
            a.push_back(vector<ll>(n, 0));
            for(int j = 0; j < n; j++) {
                a[i][j] = 0;
            }
        }
    }
    Matrix operator *(Matrix other) {
        Matrix product = Matrix(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < (n); j++) {
                for(int k = 0; k < (n); k++) {
                    product.a[i][k] += a[i][j] * other.a[j][k];
                    product.a[i][k] = product.a[i][k]%MOD;
                }
            }
        }
        return product;
    }
};

Matrix expo_power(Matrix a, ll n) {
    ll H = a.n;
    Matrix res = Matrix(H);
    res.a[0][0] = res.a[H-1][H-1] = 1;
    while(n) {
        if(n % 2) {
            res = res * a;
        }
        n /= 2;
        a = a * a;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    ll n, m, k; cin >> n >> m >> k;
    Matrix mat(n);
    for (int i = 0; i < m; i++) {
        ll a, b; cin >> a >> b; a--; b--;
        mat.a[a][b] += 1;
    }

    Matrix ans = expo_power(mat, k);
    cout << ans.a[0][n-1] << endl;
}