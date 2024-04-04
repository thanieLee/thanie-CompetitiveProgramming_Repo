#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    ll N, W; cin >> N >> W;
    ll zeroCnt = 0, oneCnt = 0, twoCnt = 0, threeCnt = 0;
    ll firstW, firstV; cin >> firstW >> firstV;
    vector<ll> weights, value;
    weights.push_back(firstW);
    value.push_back(firstV);
    zeroCnt++;
    vector<ll> zeroSum(1, 0), oneSum(1, 0), twoSum(1, 0), threeSum(1, 0), zero, one, two, three;
    zero.push_back(firstV);
    for (ll i = 1; i < N; i++){
        ll wi, vi; cin >> wi >> vi;
        if (wi == firstW) {
            zeroCnt++;
            zero.push_back(vi);
        } else if (wi == firstW+1) {
            oneCnt++;
            one.push_back(vi);
        } else if (wi == firstW+2) {
            twoCnt++;
            two.push_back(vi);
        } else {
            threeCnt++;
            three.push_back(vi);
        }

        weights.push_back(wi);
        value.push_back(vi);
    }

    sort(zero.begin(), zero.end(), greater());
    sort(one.begin(), one.end(),  greater());
    sort(two.begin(), two.end(),  greater());
    sort(three.begin(), three.end(),  greater());

    ll cur = 0;
    for (ll i : zero) {
        cur += i;
        zeroSum.push_back(cur);
    }

    cur = 0;
    for (ll i : one){
        cur += i;
        oneSum.push_back(cur);
    }
    cur = 0;
    for (ll i : two){
        cur += i;
        twoSum.push_back(cur);
    }
    cur = 0;
    for (ll i : three){
        cur += i;
        threeSum.push_back(cur);
    }


    ll ans = 0;

    for (ll j = 0; j <= zeroCnt; j++){
        for (ll k = 0; k <= oneCnt; k++){
            for (ll l = 0; l <= twoCnt; l++){
                for (ll m = 0; m <= threeCnt; m++){
                    if (j*(firstW) + k*(firstW+1) + l*(firstW+2) + m*(firstW+3) <= W) {
                        ans = max(ans, zeroSum[j]+oneSum[k]+twoSum[l]+threeSum[m]);
                    }
                }
            }
        }
    }
    
   

    cout << ans << endl;
}