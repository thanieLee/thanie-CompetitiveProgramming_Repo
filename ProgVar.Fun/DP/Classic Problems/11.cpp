#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<ll> curLine;
string line;

void readIn(){
    curLine.clear();
    string cur = "";

    for (int i = 0; i < line.size(); i++) {
        if (line[i] != ' ') {
            cur.push_back(line[i]);
        } else {
            curLine.push_back(stoll(cur)-1);
            cur = "";
        }
    }

    curLine.push_back(stoll(cur)-1);
}

int main(){
    ll size;
    vector<ll> original, priority;
    vector<ll> positions;
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    while (getline(cin, line)) {
        int sCnt = 0;
        for (int i = 0; i < line.size();  i++) {
            if (line[i] == ' ') {
                sCnt++;
            }
        }

        if (sCnt == 0) {
            size = stoll(line);
            getline(cin, line);
            readIn();
            priority.resize(size, -1);
            for (int i = 0; i < size; i++) {
                priority[curLine[i]] = i;
            }
            original = curLine;
            continue;
        }
        readIn();
        vector<int> dp(size, 1);
        vector<int> newline(size, -1);
        for (int i = 0; i < size; i++) {
            newline[original[i]] = curLine[i];
        }
        int ans = 1;
        set<int> curs = {1};
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < i; j++) {
                if (newline[i] > newline[j]) {
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            ans = max(ans, dp[i]);
        }

        cout << ans << endl;
    }
}