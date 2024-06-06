#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

int main(){
    int n; cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a.push_back(ai);
    }

    int i = 0, j = 0;
    vector<pii> ans;

    while (i < n and j < n) {
        pii test(i, j);
        if (j + 1 == n) {
            ans.push_back(test);
            i = n;
            j = n;
        } else if (a[j+1] > a[j]) {
            j++;
        } else {
            ans.push_back(test);
            j++;
            i = j;
        }
    }
    int cnt = 0;
    if (ans.size() == 1) {
        cout << ans[0].second-ans[0].first+1 << endl;
        return 0;
    } else {
        for (int i = 0; i < ans.size()-1; i++) {
            if (ans[i].second-ans[i].first == 0) {
                if (i == 0) {
                    cnt = max(cnt, ans[i+1].second-ans[i].first+1);
                } else {
                    if (a[ans[i+1].first]-a[ans[i-1].second] > 1) {
                        cnt = max(cnt, ans[i+1].second-ans[i-1].first+1);
                    }
                }
            } else {
                if (ans[i].second+1 == ans[i+1].first and a[ans[i+1].first+1]-a[ans[i].second] > 1) {
                    cnt = max(cnt, ans[i+1].second-ans[i].first+1);
                } else if (ans[i].second+1 == ans[i+1].first and a[ans[i+1].first]-a[ans[i].second-1] > 1) {
                    cnt = max(cnt, ans[i+1].second-ans[i].first+1);
                }
            }

            cnt = max(cnt, ans[i].second-ans[i].first+2);
            cnt = max(cnt, ans[i+1].second-ans[i+1].first+2);
        }
    }
    for (auto p : ans) {
        //cout << p.first << " " << p.second << endl;
    }
    cout << min(cnt, n) << endl;
}