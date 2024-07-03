#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<vector<int>> possible;
vector<uint> arr;
int n;
void gen(vector<int> cur) {
    if (cur.size() == n) {
        possible.push_back(cur);
        return;
    } 

    if (cur.size() == 0) {
        vector<int> next = {0};
        gen(next);
        return;
    }

    vector<int> next1 = cur, next2 = cur;
    next1.push_back(next1[next1.size()-1]);
    next2.push_back(next2[next2.size()-1]+1);

    gen(next1);
    gen(next2);
}

uint solve(vector<int> perm) {
    uint cur_idx = 0;
    uint cur_or = 0;
    uint ans = 0;
    for (int i = 0; i < n; i++){
        if (perm[i] == cur_idx) {
            cur_or |= arr[i];
        } else {
            cur_idx = perm[i];
            ans ^= cur_or;
            cur_or = arr[i];
        }
    }

    ans ^= cur_or;
    return ans;
}


int main(){
    cin >> n;
    for (int i = 0; i < n; i++) {
        uint ai; cin >> ai;
        arr.push_back(ai);
    }

    vector<int> temp;
    gen(temp);
    uint ans = numeric_limits<uint>::max();
    for (auto pos : possible) {
        ans = min(ans, solve(pos));
    }
    cout << ans << endl;
}