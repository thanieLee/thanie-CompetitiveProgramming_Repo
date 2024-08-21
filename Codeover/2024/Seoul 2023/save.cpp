#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;

vector<vector<vector<map<ll, ll>>>> dp_r, dp_l;
bool two = false, three = false, five = false, seven = false;

ll process(ll x) {
    ll temp = x;
    if (x == 0) return 0;
    if (!two) {
        while (temp % 2 == 0) {
            temp /= 2;
        }
    }

    if (!three) {
        while (temp % 3 == 0) {
            temp /= 3;
        }
    }

    if (!five) {
        while (temp % 5 == 0) {
            temp /= 5;
        }
    }

    if (!seven) {
        while (temp % 7 == 0) {
            temp /= 7;
        }
    }

    return temp;
}

ll ANS_MOD = 1000000007ll;

ll mod(ll x, ll m) {
	if (m == 0)
		return 0;
	if (m < 0)
		m *= -1;
	return (x % m + m) % m;
}

ll mod_add(ll x, ll y, ll m) {
    return mod(mod(x, m) + mod(y, m), m);
}

bool in_map(map<ll, ll> &x, ll y) {
    return x.find(y) != x.end();
}

ll solve(ll mx, ll k, string s) {
    if (mx == 0) return 0;
    ll len = s.size();
    vector<vector<vector<map<ll, ll>>>> dp(len+1, vector(2, vector(2, map<ll, ll>())));
    ll first_limit = s[0]-'0';

    // base cases
    dp[0][0][0][0] = mod(1, ANS_MOD);
    if (in_map(dp[0][1][0], mod(process(first_limit),k))) {
        dp[0][1][0][mod(process(first_limit),k)] = mod_add(dp[0][1][0][mod(process(first_limit),k)], 1, ANS_MOD);
    }
    else
        dp[0][1][0][mod(process(first_limit),k)] = mod(1, ANS_MOD);

    for (ll i = 1; i < first_limit; i++) {
        if (in_map(dp[0][1][1], mod(process(i),k))) {
            dp[0][1][1][mod(process(i),k)] = mod_add(1, dp[0][1][1][mod(process(i),k)], ANS_MOD);
        }
        else
            dp[0][1][1][mod(process(i),k)] = mod(1, ANS_MOD);
    }

    for (int i = 1; i < len; i++) {
        ll cur_limit = s[i]-'0';
        // has value and is not decreasing
        for (auto p : dp[i-1][1][0]) {
            if (in_map(dp[i][1][0], mod(process(p.first*cur_limit),k))) {
                dp[i][1][0][mod(process(p.first*cur_limit),k)] = mod_add(p.second, dp[i][1][0][mod(process(p.first*cur_limit),k)], ANS_MOD);
            }
            else
                dp[i][1][0][mod(process(p.first*cur_limit),k)] = mod(p.second, ANS_MOD);
        }

        // has value and is decreasing; 
        for (ll digit = 0; digit <= 9; digit++) {
            // previous has value and is decreasing
            for (auto p : dp[i-1][1][1]) {
                if (in_map(dp[i][1][1], mod(process(digit*p.first),k))) {
                    dp[i][1][1][mod(process(digit*p.first),k)] = mod_add(p.second, dp[i][1][1][mod(process(digit*p.first),k)], ANS_MOD);
                } else {
                    dp[i][1][1][mod(process(digit*p.first),k)] = mod(p.second, ANS_MOD);
                }
            }
            // no value + starting a new value
            if (digit != 0) {
                if (in_map(dp[i][1][1], mod(process(digit),k))) {
                    dp[i][1][1][mod(process(digit),k)] = mod_add(1, dp[i][1][1][mod(process(digit),k)], ANS_MOD);
                }
                else
                    dp[i][1][1][mod(process(digit),k)] = mod(1, ANS_MOD);
            }
        }

        // has value and decreasing
        for (ll digit = 0; digit < cur_limit; digit++) {
            // previous has value and is not decreasing
            for (auto p : dp[i-1][1][0]) {
                if (in_map(dp[i][1][1], mod(process(digit*p.first),k))) {
                    dp[i][1][1][mod(process(digit*p.first),k)] = mod_add(p.second, dp[i][1][1][mod(process(digit*p.first),k)], ANS_MOD);
                } else {
                    dp[i][1][1][mod(process(digit*p.first),k)] = mod(p.second, ANS_MOD);
                }
            }
        }

        // no value and decreasing
        if (in_map(dp[i][0][1], 0)) {
            dp[i][0][1][0] = mod_add(1, dp[i][0][1][0], ANS_MOD);
        }
        else
            dp[i][0][1][0] = mod(1, ANS_MOD);
    }

    ll ans = 0;
    if (dp[len-1][1][0].find(0) != dp[len-1][1][0].end()) {
        ans = mod_add(dp[len-1][1][0][0], ans, ANS_MOD);
    }
    
    if (dp[len-1][1][1].find(0) != dp[len-1][1][1].end()) {
        ans = mod_add(ans, dp[len-1][1][1][0], ANS_MOD);
    }

    return mod(ans, ANS_MOD);
}

pair<ll, string> read() {
    __int128 x = 0, f = 1;
    string o = "";
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        o += ch;
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        o += ch;
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return {x * f, o};
}

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main(){
        auto k_p = read();
        auto l_p = read();
        auto r_p = read();
        ll k = k_p.first;
        ll l = l_p.first;
        ll r = r_p.first;
        string k_s = k_p.second;
        string k_l = l_p.second;
        string k_r = r_p.second;
        ll temp = k;
        while (temp % 2 == 0) {
            two = true;
            temp /= 2;
        }
        while (temp % 3 == 0) {
            three = true;
            temp /= 3;
        }
        while (temp % 5 == 0) {
            five = true;
            temp /= 5;
        }
        while (temp % 7 == 0) {
            seven = true;
            temp /= 7;
        }
        //cout << brute(r, k) - brute(l, k) << endl;
        //k /= temp;
        //cout << temp << endl;

        ll ans_1 = solve(r, k, k_r);
        ll ans_2 = solve(l, k, k_l);
        bool can = false;
        ll temp1 = 1;
        for (int i = 0; i < k_l.size(); i++) {
            temp1 *= k_l[i]-'0';
        }
        if (mod(temp1, k) == 0) {
            ans_2--;
        }
        //cout << k << endl;
        print(mod(ANS_MOD + ans_1 - ans_2 + ANS_MOD, ANS_MOD));
} 