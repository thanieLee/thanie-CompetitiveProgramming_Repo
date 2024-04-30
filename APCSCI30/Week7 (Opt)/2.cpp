#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
pair<ll, ll>,
null_type,
less<pair<ll ,ll>>,
rb_tree_tag,
tree_order_statistics_node_update> ordered_set;

vector<int> ranks, parent, section;

vector<ordered_set*> groups;
int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

void connect(int i, int j) {
    int u = find(i);
    int v = find(j);

    if (u == v)
        return;
    if (ranks[u] < ranks[v]) {
        parent[u] = v;
        ranks[v] += ranks[u];
    } else {
        parent[v] = u;
        ranks[u] += ranks[v];
    }
}

int main(){
    int n, q; cin >> n >> q;
    ranks.resize(n); parent.resize(n); groups.resize(n);
    for (int i = 0; i < n; i++) {
        int ci; cin >> ci; ci--;
        section.push_back(ci);
        ranks[i] = 1;
        parent[i] = i;
    }

    for (int i = 0; i < n; i++) {
        groups[i] = new ordered_set;
        groups[i]->insert({section[i], i});
    }

    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int a, b; cin >> a >> b; a--; b--;
            int aParent = find(a), bParent = find(b);
            //cout << "test: " << aParent << " " << bParent << endl;
            if (aParent == bParent) continue;
            
            ordered_set* aList = groups[aParent];
            ordered_set* bList = groups[bParent];
            //cout << aList->size() << " " << bList->size() << endl;
            if (aList->size() > bList->size()) {
                for (auto it = bList->begin(); it != bList->end(); it++) {
                    aList->insert(*it);
                }
                groups[bParent] = aList;
            } else {
                for (auto it = aList->begin(); it != aList->end(); it++) {
                    bList->insert(*it);
                }
                groups[aParent] = bList;
            }
            
            connect(a, b);
        } else {
            int x, y; cin >> x >> y; x--; y--;
            int xParent = find(x);
            //cout << xParent << endl;
            ordered_set* xList = groups[xParent];
            int lower = xList->order_of_key({y, -1}), upper = xList->order_of_key({y+1, -1});
            cout << max(0, upper-lower) << endl;
        }
    }
}