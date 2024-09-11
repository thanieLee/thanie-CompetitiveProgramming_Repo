#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int h1, d1, t1, h2, d2, t2; cin >> h1 >> d1 >> t1 >> h2 >> d2 >> t2;
    float time = 0;
    float p1r = 0, p2r = 0;
    while (true) {
        if (h1 <= 0 and h2 <= 0) {
            cout << "draw" << endl;
            break;
        } else if (h1 <= 0) {
            cout << "player two" << endl;
            break;
        } else if (h2 <= 0) {
            cout << "player one" << endl;
            break;
        }



        if (p1r == 0) {
            h2 -= d1;
        }

        if (p2r == 0) {
            h1 -= d2;
        }


        p1r += 0.5;
        p2r += 0.5;
        time += 0.5;
        if (p1r == t1) {
            p1r = 0;
        } 

        if (p2r == t2) {
            p2r = 0;
        }
    }
}