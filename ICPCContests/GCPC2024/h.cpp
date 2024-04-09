#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll MOD = 1000000007;

bool cmp(pair<ll, vector<ll>> &x, pair<ll, vector<ll>> &y) {
    return x.first < y.first;
}

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


int main(){
    ll n; cin >> n;
    ll mx = -1;

    if (n == 0) {
        cout << ".##" << endl;
        cout << "##." << endl;
        return 0;
    }

    vector<ll> fib = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141};
    ll lb = 0, ub = fib.size()-1;

    multiset<pair<ll, ll>> s1, s2;
    vector<vector<ll>> lists1, lists2;
    srand(time(0));
    while (mx++ <= 700000) {
        ll cnt = 0, prod = 1;
        vector<ll> cur;
        int temp = 0;
        while (cnt < 97) {
            ll ran = (rand() % min((ub - lb + 1), 97-cnt)) + lb;
            cnt += ran+2;
            cur.push_back(ran+1);
            temp += ran+1;
            prod *= fib[ran];
            prod = mod(prod, MOD);
        }
        lists1.push_back(cur);
        s1.insert({prod, mx});
    }
    mx = -1;
    srand(time(0));
    while (mx++ <= 700000) {
        ll cnt = 0, prod = 1;
        vector<ll> cur;
        int temp = 0;
        while (cnt < 97) {
            ll ran = (rand() % min((ub - lb + 1), 97-cnt)) + lb;
            cnt += ran+2;
            cur.push_back(ran+1);
            temp += ran+1;
            prod *= fib[ran];
            prod = mod(prod, MOD);
        }
        lists2.push_back(cur);
        s2.insert({prod, mx});
    }

    for (auto it = s1.begin(); it != s1.end(); it++){
        ll inv = mod_inv(it->first, MOD);
        ll nextVal = mod(inv*n, MOD);
        auto s2Test = s2.lower_bound({nextVal, -1});
        if (s2Test->first == nextVal) {
            vector<ll> l1 = lists1[it->second], l2 = lists2[s2Test->second];
            string output = "";
            for (int i = 0; i < l1.size(); i++){
                for (int j = 0; j < l1[i]; j++) {
                    output.push_back('.');
                }

                output.push_back('#');
            }

            for (int i = 0; i < l2.size(); i++){
                for (int j = 0; j < l2[i]; j++) {
                    output.push_back('.');
                }
                if (i != l2.size()-1)
                    output.push_back('#');
            }

            cout << output << endl;
            cout << output << endl;
            
            return 0;
        }
    }
}