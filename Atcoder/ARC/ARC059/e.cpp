#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
vector<ll> a, b;
ll n, c;
vector<ll> gDP;
vector<vector<ll>> fDP; 
ll MOD = 1e9+7;
vector<vector<ll>> modPowTable;

ll mod(ll x, ll m) {
	if (m == 0)
		return 0;
	if (m < 0)
		m *= -1;
	return (x % m + m) % m;
}

ll mod_pow(ll x, ll y, ll p) 
{ 
    ll res = 1;
    x = mod(x,p);
    if (x == 0) return 0;
    while (y > 0) 
    { 
        if (y & 1) 
            res = mod(res*x, p);
        y = y >> 1;
        x = mod(x*x, p);
        res = mod(res, p);
    } 
    return res; 
}


int main(){
    cin >> n >> c;
    gDP.resize(n+1, -1);
    fDP.resize(n+1, vector<ll>(c+1, 0));
    modPowTable.resize(n+1, vector<ll>(c+1, 0));    

    for (int i = 0; i < n; i++){
        ll ai; cin >> ai;
        a.push_back(ai);
    }

    for (int i = 0; i < n; i++){
        ll bi; cin >> bi;
        b.push_back(bi);
    }

    for (int k = 0; k < n; k++){
        for (ll j = a[k]; j <= b[k]; j++) {
            ll temp = 1;
            for (int i = 0; i < c+1; i++){
                modPowTable[k][i] += temp;
                modPowTable[k][i] %= MOD;
                temp *= j;
                temp %= MOD;
            }
        }
    }

    fDP[n][0] = 1;

    for (int x = n-1; x >= 0; x--) {
        for (int d = 0; d <= c; d++) {
            ll cnt = 0;
            for (int j = 0; j <= d; j++) {
                cnt += (modPowTable[x][j]*fDP[x+1][d-j])%MOD;
            }
            cnt %= MOD;
            fDP[x][d] = cnt;
        }
    }

    cout << fDP[0][c] << endl;
}