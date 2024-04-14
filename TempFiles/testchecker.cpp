#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int permcount = 0;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
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

    for (int i = 0; i < n; i++) {
        int a = inf.readInt(1, m, "swapA");
        inf.readSpace();
        int b = inf.readInt(1, m, "swapB");
        inf.readEoln();
    }

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();
    for (int i = 0; i < n; i++) {
        string query = inf.readToken();
        if (query == "PERM") {
            permcount++;
        } 
        inf.readEoln();
    }

    for (int i = 0; i < permcount; i++) {
        for (int j = 0; j < m; j++) {
            int jCur = ans.readInt();
            int pCur = ouf.readInt();

            if (jCur != pCur) {
                quitf(_wa, "Permutation printed is incorrect");
            }

            if (j < m-1) {
                ans.readSpace();
                ouf.readSpace();
            }
        }
        ans.readEoln();
        ouf.readEoln(); 
    }

    if (!ouf.eof()) {
        quitf(_wa, "Incorrect number of permutations");
    }

    quitf(_ok, "permutation correct");
}