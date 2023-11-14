#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef long long int ll;


bool cmp(pair<ll, ll> &x, pair<ll, ll> &y){
    return x.second < y.second;
}
int main(){
    ll N, D, A; cin >> N >> D >> A;
    vector<pair<ll, ll>> monsters;

    for (int i = 0; i < N; i++){
        ll x, h; cin >> x >> h;
        monsters.push_back({x, h});
    }

    sort(monsters.begin(), monsters.end());
    ll idx = 1;
    deque<pair<ll, ll>> q;
    q.push_back(monsters[0]);
    ll del = 0;
    ll ans = 0;
    while (!q.empty() or idx != N){
        if (q.empty() and idx != N) {
            q.push_back({monsters[idx].first, monsters[idx].second+del});
            idx++;
        }
        pair<ll, ll> cur = q.front();
    
        if (idx < N){
            while (cur.first+2*D >= monsters[idx].first){
                q.push_back({monsters[idx].first, monsters[idx].second+del});
                idx++;
                if (idx == N) break;
            }
        }
      

        ll diff = cur.second-del;
        ll num = ceil((double)diff/(double)A);
        ans += num;
        del += num*A;

        while (q.front().second <= del) {
            q.pop_front();
            if (q.empty()) break;
        }
    }
    cout << ans << endl;
}