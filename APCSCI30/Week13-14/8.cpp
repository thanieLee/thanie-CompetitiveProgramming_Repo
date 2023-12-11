#include <bits/stdc++.h>
using namespace std;

int n, N;
vector<int> equiv, sa, pos;
vector<pair<int, int>> equiv_pair;
vector<int> lcp;

void suffix() {
    for (int i = 0; i < N; i++)
        sa[i] = i, pos[i] = S[i];

    for (gap = 1;; gap <<= 1) {
        sort(sa, sa+N, comp);
        for (int i = 0; i < N-1; i++)
            tmp[i+1] = tmp[i] + comp(sa[i], sa[i+1]);
        for (int i = 0; i < N; i++)
            pos[sa[i]] = tmp[i];
        if (tmp[N - 1] == N - 1)
            break;
    }
}


void buildLCP(string& s){
    vector<int> inv(n+1);

    for (int i = 0; i < suffix.size(); i++){
        inv[suffix[i]] = i;
    }
    
    for (int i = 0, k = 0; i < n; i++){
        if (inv[i] != n-1) {
            for (int j = suffix[inv[i] + 1]; s[i+k] == s[j+k]; k++);
                lcp[inv[i]] = k;
                if (k > 0) k--;
        } 
    }
}



int main(){
    string s; cin >> s;
    n = s.size();
    equiv.resize(n+1);
    suffix.resize(n+1);
    equiv_pair.resize(n+1);
    lcp.resize(n, 0);
    make_suffix_array(s);
    buildLCP(s);
    
    pair<int, int> cur = {0, 0};

    for (int i = 0; i < n; i++){
        if (lcp[i] > cur.first){
            cur = {lcp[i], i};
        }
    }

    if (cur.first == 0) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 0; i < cur.first; i++){
        cout << s[suffix[cur.second] + i];
    }
    cout << endl;

}