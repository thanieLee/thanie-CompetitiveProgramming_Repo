#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type,
less<pair<int, int>>, rb_tree_tag,
tree_order_statistics_node_update>
ordered_multiset;


int main(){
    int n; cin >> n;
    vector<int> a;
    vector<pair<int, int>> pairs;
    ordered_multiset orig, orig_reverse;
    orig.find_by_order
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
        pairs.push_back({ai, i});
        orig.insert({ai, i});
        orig_reverse.insert({ai, i});
    }

    sort(pairs.begin(), pairs.end());
    vector<vector<int>> ans(n+1, vector<int>());

    for (int i = 0; i < n; i++) {
        pii cur = pairs[i];
        auto orig_ptr = find(orig.begin(), orig.end(), cur);
        auto orig_reverse_ptr = find(orig_reverse.begin(), orig_reverse.end(), cur);




    }

    


    
}
