#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();
    vector<bool> perm(m, false);
    for (int i = 0; i < m; i++) {
        int cur = inf.readInt(1, m, "cur");
        cur--;
        if (i < m-1) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    int falseCount = 0;
    for (bool b : perm) {
        if (not b) {
            falseCount++;
        }
    }

    ensure(falseCount == 0);

    for (int i = 0; i < n; i++) {
        int a = inf.readInt(1, m, "swapA");
        inf.readSpace();
        int b = inf.readInt(1, m, "swapB");
        ensure(a != b);
        inf.readEoln();
    }

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();
    for (int i = 0; i < n; i++) {
        string query = inf.readToken();
        ensure(query == "PERM" or query == "SWAP");
        inf.readSpace();
        if (query == "PERM") {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int r = inf.readInt(l, n, "r");
            ensure(l <= r);
        } else if (query == "SWAP") {
            int x = inf.readInt(1, n, "x");
            inf.readSpace();
            int a = inf.readInt(1, m, "a");
            inf.readSpace();
            int b = inf.readInt(1, m, "b");
            ensure(a != b);
        }
        inf.readEoln();
    }


}