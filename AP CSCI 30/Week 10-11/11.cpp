#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef long double ld;
typedef vector<int> vint;
typedef pair<int, int> pint;
#define MAX 1000000000
#define rep(i, n) for (int i = 0; i < n; i++)
#define revrep(i, n) for (int i = n-1; i >= 0; i--)
#define repk(i, n, k) for (int i = k; i < n; i++)
struct val {
  int value = 0;  
};

bool cmp(pair<int, int> &x, pair<int, int> &y){
    if (x.first == y.first) return x.second > y.second;
    return x.first < y.first;
}

int main(){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<pair<int, int>> queries;
    for (int i = 0; i < n; i++){
        int a, b; cin >> a >> b;
        queries.push_back({a, 1});
        queries.push_back({b, -1});
    }
    
    sort(queries.begin(), queries.end(), cmp);
    int cnt = 0;
    int prev = -1000000001;
    bool inc = false;
    vector<pair<int, int>> satis;
    
    for (size_t i = 0; i < queries.size(); i++) {
        //cout << queries[i].first << " " << queries[i].second << endl;
    }
    
    for (int i = 0; i < queries.size(); i++){
        pair<int, int> cur = queries[i];
        cnt += cur.second;
        if (i < queries.size()-1) {
            while (queries[i+1].first == cur.first and queries[i+1].second >= 0){
                i++;
                cur = queries[i];
                cnt += cur.second;

                if (i == queries.size()-1) break;
            }
        }
        if (cnt >= k and !inc){
            inc = true;
            prev = cur.first;
        }

        if (i < queries.size()-1) {
            while (queries[i+1].first == cur.first and queries[i+1].second < 0){
                i++;
                cur = queries[i];
                cnt += cur.second;

                if (i == queries.size()-1) break;
            }
        }

        if (cnt < k and inc){
            inc = false;
            satis.push_back({prev, cur.first});
        }
    }
    
    cout << satis.size() << endl;
    
    for (int i = 0; i < satis.size(); i++){
        pair<int, int> cur = satis[i];
        cout << cur.first << " " << cur.second << endl;
    }
    
}
