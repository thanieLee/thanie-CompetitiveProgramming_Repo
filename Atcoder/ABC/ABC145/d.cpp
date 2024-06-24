#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long int ll;
ll MOD = 1000000007;
int cnt = 0;

ll mod(ll x, ll m) {
	if (m == 0)
		return 0;
	if (m < 0)
		m *= -1;
	return (x % m + m) % m;
}

ll extended_euclid(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll g = extended_euclid(b, mod(a, b), x, y);
	ll z = x - a/b*y;
	x = y;
	y = z;
	return g;
}

ll mod_inv(ll a, ll m) {
	ll x, y;
	ll g = extended_euclid(a, m, x, y);
	if (g == 1 || g == -1)
		return mod(x * g, m);
	return 0;
}

ll mod_div(ll a, ll b, ll m) {
	a = mod(a, m);
	ll inv = mod_inv(b, m);
	return mod(inv * a, m);
}

set<pair<int, int>> test;
int x, y;
void count(int xi, int yi) {
    if (xi > x or yi > y){
        return;
    }
    if (xi == x and yi == y) {
        cnt++;
        return;
    }

    test.insert({xi, yi});
    

    count(xi+1, yi+2);
    count(xi+2, yi+1);

}

int main(){
    cin >> x >> y;

    vector<pair<int, int>> top, bot;
    int i = 1, j = 2;
    while (i <= x or j <= y) {
        top.push_back({i, j});
        i+=1;
        j+=2;
    }
    i = 2, j = 1;
    while (i <= x or j <= y) {
        bot.push_back({i, j});
        i+=2;
        j+=1;
    }

    vector<int> fact;
    fact.push_back(1);
    int cum = 1;
    for (int i = 1; i <= 1000000; i++) {
        cum *= i;
        cum %= MOD;
        fact.push_back(cum);
    }
    if ((x%3) == (y%3) and x%3 != 0) {
        cout << 0 << endl;
    } else if (x==0 and y==0) {
        cout << 1 << endl;
    } else {
        int idx = 0;
        while (true) {
            
            pii hi = top[idx];
            pii low = bot[idx];
            //cout << hi.first << " " << hi.second << endl;
            //cout << low.first << " " << low.second << endl;
            //cout << abs(hi.first - x) << " " << abs(low.first-x) << " " << abs(hi.second-y) << " " <<abs(low.second-y) << endl; 
            if (((double) hi.second-y)/( (double)hi.first-x) == ((double)low.second-y)/((double)low.first-x)) {
                break;
            }
            idx++;
        }
        idx++;
        int dist = abs(top[idx-1].first-x);
        cout << mod_div((ll)fact[idx], (ll)fact[dist]*(ll)fact[idx-dist], MOD) << endl;
        pii hi = top[idx];
        pii low = bot[idx];
        cout << hi.first << " " << hi.second << endl;
        cout << low.first << " " << low.second << endl;
        cout << idx << endl;
    }

}