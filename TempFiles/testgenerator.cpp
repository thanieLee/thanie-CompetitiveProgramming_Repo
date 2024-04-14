#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int q = atoi(argv[3]);
    cout << n << " " << m << endl;
    vector<int> perm(m);
    for (int i = 1; i <= m; i++) {
        perm[i-1] = i;
    }
    shuffle(perm.begin(), perm.end());
    
    for (int i = 0; i < m; i++) {
        cout << perm[i] << " ";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        int a = rnd.next(1, m);
        int b = rnd.next(1, m);
        while (a == b) {
            b = rnd.next(1, m);
        }
        cout << a << " " << b << endl;
    }
    
    cout << q << endl;
    for (int i = 0; i < q; i++) {
        int ne = rnd.next(0, 1);
        if (ne == 0) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            cout << "PERM " << l << " " << r << endl;
        } else {
            int x = rnd.next(1, n);
            int a = rnd.next(1, m);
            int b = rnd.next(1, m);
            while (a == b) {
                b = rnd.next(1, m);
            }
            cout << "SWAP " << x << " " << a << " " << b << endl;
        }
    }
}