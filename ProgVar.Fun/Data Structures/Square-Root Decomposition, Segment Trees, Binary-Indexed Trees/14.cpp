#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define mp make_pair
using namespace std;
using namespace __gnu_pbds;
typedef pair<ll, ll> pll;
typedef tree<pll, null_type, less<pll>, rb_tree_tag, tree_order_statistics_node_update> OST;

const int N = 200001;
ll h, w, m;
vector<set<ll>> grid;


int main(){
    cin >> h >> w >> m;
    for (int i = 0; i < m; i++) {
        ll x, y; cin >> x >> y; x--; y--;
        grid[x]
    }

    cout << query(2, 2) << endl;


}