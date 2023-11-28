// This is my second iteration of Hanjo 2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 998244353
ll H, W;
ll mod(ll x){
    return ((x%MOD)+MOD)%MOD;
}

struct Matrix {
    vector<vector<ll>> a;

    Matrix() {
        for(int i = 0; i < 1<<H; i++) {
            a.push_back(vector<ll>(1<<H, 0));
            for(int j = 0; j < 1<<H; j++) {
                a[i][j] = 0;
            }
        }
    }
    Matrix operator *(Matrix other) {
        Matrix product = Matrix();
        for(int i = 0; i < 1<<H; i++) {
            for(int j = 0; j < (1<<H); j++) {
                for(int k = 0; k < (1<<H); k++) {
                    product.a[i][k] += a[i][j] * other.a[j][k];
                    product.a[i][k] = mod(product.a[i][k]);
                }
            }
        }
        return product;
    }
};

Matrix expo_power(Matrix a, long long n) {
    Matrix res = Matrix();
    res.a[0][0] = res.a[(1<<H)-1][(1<<H)-1] = 1;
    while(n) {
        if(n % 2) {
            res = res * a;
        }
        n /= 2;
        a = a * a;
    }
    return res;
}

int main() {
    cin >> H >> W;


    vector dp(2, vector<ll>(1<<H, 0));
    vector<ll> fib = {1, 2, 3, 5, 8, 13};
    dp[0][0] = 1;

    for (int i = 0; i < 1<<H; ++i) {
        for (int j = 0; j < H; ++j) {
            if ((i & (1<<j)) == 0) {
                dp[0][i | (1<<j)] += dp[0][i];
                if (j == 0) continue;
                if ((i & (1<<(j-1))) == 0) {
                    cout << i << endl;
                    if (i == 3)
                        cout << ((i & ~(1<<j)) & ~(1<<(j-1))) << " test" << endl;
                    dp[0][(i | (1<<j)) | (1<<(j-1))] += dp[0][i];  
                }
            }
        }
    }

    ll temp = 0;
    for (int i = 0; i < 1<<H; i++){
        temp += dp[0][i];
    }

    cout << temp << endl;
    Matrix test = Matrix();
    for (int j = 0; j < 1<<H; ++j) {
        for (int k = 0; k < 1<<H; ++k) {
            bool can = true;
            for (int l = 0; l < H; ++l) {
                if ((j & (1<<l)) == 0 and (k & (1<<l)) == 0) can = false;
            }

            if (can){
                ll cur = 1;
                for (int l = 0; l < H; ++l) {
                    if ((k & (1<<l)) == 0 or (j & (1<<l)) == 0) continue;
                    ll cnt = 0;
                    while ((k & (1<<(l+1))) and (j & (1<<(l+1)))) {
                        cnt++;
                        l++;
                    }

                    cur *= fib[cnt];
                }
                dp[1][k] += dp[0][j] * cur;
                test.a[k][j] = cur;
                dp[1][k] = mod(dp[1][k]);
            }
        }
    }


    Matrix ans = expo_power(test, W+1);

    cout << mod(ans.a[(1<<H)-1][0]) << endl;
}