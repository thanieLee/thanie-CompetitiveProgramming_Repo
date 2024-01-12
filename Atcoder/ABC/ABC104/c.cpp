#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct truple{
    int first, second, third;

    void set(int f, int s, int t){
        first = f;
        second = s;
        third = t;
    }
};



int main(){
    int d, g; cin >> d >> g;
    vector<int> p, c;
    int mx = 0;
    for (int i = 0; i < d; i++){
        int pi, ci; cin >> pi >> ci;
        mx += pi;
        p.push_back(pi);
        c.push_back(ci);
    }

    int ans = mx;   
    for (int cur = 1; cur <= mx; cur++){

        int curT = cur;
        vector<int> pc = p, cc = c;
        truple temp;
        int points = 0;
        //cout << cur << endl;
        while (curT){
            temp.set(0, -1, -1);
            for (int i = 0; i < d; i++){
                if (pc[i] == 0) continue;
                if (pc[i] <= curT) {
                    if (temp.first == pc[i] * (i+1) * 100 + cc[i]) {
                        if (temp.second > pc[i]) {
                            temp.second = pc[i];
                            temp.third = i;
                        }
                    } else if (temp.first < pc[i] * (i+1) * 100 + cc[i]) {
                        temp.first = pc[i] * (i+1) * 100 + cc[i];
                        temp.second = pc[i];
                        temp.third = i;
                    }
                } else if (pc[i] > curT) {
                    if (temp.first == curT * (i+1) * 100) {
                        if (temp.second > curT) {
                            temp.second = curT;
                            temp.third = i;
                        }
                    } else if (temp.first < curT * (i+1) * 100) {
                        temp.first = curT * (i+1) * 100;
                        temp.second = curT;
                        temp.third = i;
                    }
                }
                if (cur == 66)
                    cout << temp.first << endl;
            }
            if (cur == 66)
                cout << temp.first << " " << temp.second << " " << temp.third << " " << curT <<  endl;
            if (temp.third > -1){
                points += temp.first;
                curT -= temp.second;
                pc[temp.third] -= temp.second;
            }

        }

        if(cur == 66)
            cout << cur << " " << points << endl;
        if (points >= g) {
            ans = min(cur, ans);
        }
    }

    cout << ans << endl;
}