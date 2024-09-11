#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n; cin >> n;
    map<string, string> bottles;
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        s.pop_back();
        if (find(s.begin(), s.end(), '.') != s.end())
            while (s[s.size()-1] == '0') {
                s.pop_back();
                if (s[s.size()-1] == '.') {
                    s.pop_back();
                    break;
                }
            }
        if (bottles.find(s) == bottles.end()) {
            bottles[s] = alpha;
            next_permutation(alpha.begin(), alpha.end());
        
        }
        cout << bottles[s] << endl;
    }
}