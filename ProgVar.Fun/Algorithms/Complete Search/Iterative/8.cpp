#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int ipToNum(string ip) {
    vector<int> periods;
    int len = ip.size();
    for (int i = 0; i < len; i++) {
        if (ip[i] == '.') periods.push_back(i);
    }

    string first = ip.substr(0, periods[0]);
    string sec = ip.substr(periods[0]+1, periods[1]-periods[0]-1);
    string third = ip.substr(periods[1]+1, periods[2]-periods[1]-1);
    string fourth = ip.substr(periods[2]+1, len-periods[2]-1);
    
    int firstNum = stoi(first);
    int secNum = stoi(sec);
    int thirdNum = stoi(third);
    int fourthNum = stoi(fourth);

    int ans = 0;
    ans |= (firstNum<<24);
    ans |= (secNum<<16);
    ans |= (thirdNum<<8);
    ans |= fourthNum;

    return ans;
}

string numToStr(int num) {
    int shift = 255;
    int firstNum = num & (shift<<24);
    int secNum = num & (shift<<16);
    int thirdNum = num & (shift<<8);
    int fourthNum = num & (shift);

    string first = to_string(((firstNum>>1)&~(1<<31))>>23);
    string sec = to_string(secNum>>16);
    string third = to_string(thirdNum>>8);
    string fourth = to_string(fourthNum);
    return first + "." + sec + "." + third + "." + fourth;
}

int main(){
    int n, k; cin >> n >> k;
    vector<string> ips;
    vector<int> ip_nums;
    for (int i = 0; i < n; i++) {
        string cur_ip; cin >> cur_ip;
        ipToNum(cur_ip);
        ips.push_back(cur_ip);
        ip_nums.push_back(ipToNum(cur_ip));
    }
    int sub = -1;
    int ans = 3;
    for (int i = 0; i < 31; i++) {
        sub &= ~(1<<i);
        set<int> networks;
        for (int j = 0; j < n; j++) {
            networks.insert(ip_nums[j] & sub);
        }
        if (networks.size() == k) {
            ans = sub;
        }
    }

    if (ans == 3) {
        cout << -1 << endl;
    } else {
        cout << numToStr(ans) << endl; 
    }
}