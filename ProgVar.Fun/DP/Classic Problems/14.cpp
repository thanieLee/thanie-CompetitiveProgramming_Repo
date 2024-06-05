#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
ll INF = 1000000000000000000;

struct project {
    ll a, b, p;

    project(ll a, ll b, ll p) : a(a), b(b), p(p){

    }
};


bool cmp(project &x, project &y) {
    if (x.a == y.a) {
        return x.b < y.b;
    }

    return x.a < y.a;
}

int main(){
    int n; cin >> n;

    vector<project> arr;
    for (int i = 0; i < n; i++) {
        ll ai, bi, pi; cin >> ai >> bi >> pi;
        project cur(ai, bi, pi);

        arr.push_back(cur);
    }

    sort(arr.begin(), arr.end(), cmp);


    set<ll> s;
    s.insert(0);
    ll ans = 0;
    priority_queue<pll> temp;
    for (int i = 0; i < n; i++) {
        if (!temp.empty()) {
            while (-temp.top().first < arr[i].a) {
                s.insert(temp.top().second);
                temp.pop();
                if (temp.empty()) break;
            }
        }

        ans = max(*s.rbegin() + arr[i].p, ans);
        temp.push({-arr[i].b, *s.rbegin() + arr[i].p});
    }

    cout << ans << endl;
}