#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

string f0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
string start = "What are you doing while sending \"";
string mid = "\"? Are you busy? Will you send \"";
string end = "\"?";


char solve(ll n, ll k, vector<ll> &length) {
    
}

int main(){
    int q; cin >> q;

    vector<ll> length(1, f0.size());

    for (int i = 1; i <= 55; i++) {
        length.push_back(length[i-1]*2 + start.size() + mid.size() + 2);
    }
    while (q--) {
        ll n, k; cin >> n >> k;
        cout << solve(n, k-1, length);
    }
} 