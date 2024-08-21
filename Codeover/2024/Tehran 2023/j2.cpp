#include<bits/stdc++.h>
using namespace std;

struct rmq {
    int n, *vals, *deltas;
    rmq(vector<int> &ar) {
        n = ar.size();
        vals = new int[4*n];
        deltas = new int[4*n];
        build(ar, 1, 0, n-1);
    }
    
    void build(vector<int> &ar, int p, int i, int j) {
        deltas[p] = 0;
        if (i == j) {
            vals[p] = ar[i];
        }
        else {
            int k = (i + j) / 2;
            build(ar, p<<1, i, k);
            build(ar, p<<1|1, k+1, j);
            pull(p);
        }
    }
    
    void pull(int p) {
        vals[p] = max(vals[p<<1], vals[p<<1|1]);
    }

    void push(int p, int i, int j) {
        if (deltas[p]) { 
            vals[p] += deltas[p];
            if (i != j) {
                deltas[p<<1] += deltas[p];
                deltas[p<<1|1] += deltas[p];
            }
            deltas[p] = 0;
        }
    }

    // i, j starts at 0, n-1
    void update(int _i, int _j, int v, int p, int i, int j) {
        push(p, i, j);
        // query overlaps or equates i, j
        if (_i <= i && j <= _j) {
            deltas[p] += v;
            push(p, i, j);
        }
        // no overlap
        else if (_j < i || j < _i) {}
        else {
            int k = (i + j) / 2;
            update(_i, _j, v, p<<1, i, k);
            update(_i, _j, v, p<<1|1, k+1, j);
            pull(p);
        }
    }

    int query(int _i, int _j, int p, int i, int j) {
        push(p, i, j);
        if (_i <= i && j <= _j)
            return vals[p];
        else if (_j < i || j < _i)
            return -1;
        else {
            int k = (i + j) / 2;
            return  max(query(_i, _j, p<<1, i, k),
                    query(_i, _j, p<<1|1, k+1, j));
        }
    }

    void update(int _i, int _j, int v) {
        update(_i, _j, v, 1, 0, n-1);
    }

    int query(int _i, int _j) {
        return query(_i, _j, 1, 0, n-1);
    }
};

struct rsq {
    int n, *vals, *deltas;
    rsq(vector<int> &ar) {
        n = ar.size();
        vals = new int[4*n];
        deltas = new int[4*n];
        build(ar, 1, 0, n-1);
    }
    
    void build(vector<int> &ar, int p, int i, int j) {
        deltas[p] = 0;
        if (i == j) {
            vals[p] = ar[i];
        }
        else {
            int k = (i + j) / 2;
            build(ar, p<<1, i, k);
            build(ar, p<<1|1, k+1, j);
            pull(p);
        }
    }
    
    void pull(int p) {
        vals[p] = vals[p<<1] + vals[p<<1|1];
    }

    void push(int p, int i, int j) {
        if (deltas[p]) { 
            vals[p] += (j - i + 1) * deltas[p];
            if (i != j) {
                deltas[p<<1] += deltas[p];
                deltas[p<<1|1] += deltas[p];
            }
            deltas[p] = 0;
        }
    }

    // i, j starts at 0, n-1
    void update(int _i, int _j, int v, int p, int i, int j) {
        push(p, i, j);
        // query overlaps or equates i, j
        if (_i <= i && j <= _j) {
            deltas[p] += v;
            push(p, i, j);
        }
        // no overlap
        else if (_j < i || j < _i) {}
        else {
            int k = (i + j) / 2;
            update(_i, _j, v, p<<1, i, k);
            update(_i, _j, v, p<<1|1, k+1, j);
            pull(p);
        }
    }

    int query(int _i, int _j, int p, int i, int j) {
        push(p, i, j);
        if (_i <= i && j <= _j)
            return vals[p];
        else if (_j < i || j < _i)
            return 0;
        else {
            int k = (i + j) / 2;
            return  query(_i, _j, p<<1, i, k) +
                    query(_i, _j, p<<1|1, k+1, j);
        }
    }

    void update(int _i, int _j, int v) {
        update(_i, _j, v, 1, 0, n-1);
    }

    int query(int _i, int _j) {
        return query(_i, _j, 1, 0, n-1);
    }
};

int main(){

    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> a(n);
    int mnval = (int)1e9;
    for (int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i;
        mnval = min(mnval, a[i].first);
    } 
    sort(a.begin(), a.end());

    vector<int> tmp1(n, 0), tmp2(n-k+1, 0);
    rsq segsum(tmp1);
    rmq segmax(tmp2);
    a.push_back({-1, -1}); // garbage
    int prev = mnval;
    vector<int> ans(n, -1);
    queue<int> q;

    for (auto &[val, i] : a){
        if (prev != val){
            while (!q.empty()){
                int ii = q.front();
                q.pop();
                ans[ii] = segmax.query(max(0, ii-k+1), min(n-k, ii));
            }
        }
        if (val == -1) break;

        segsum.update(i, i, 1);
        segmax.update(max(0, i-k+1), min(n-k, i), 1);
        q.push(i);
        prev = val;
    }

    for (auto e : ans) cout << k+1-e << " "; cout << endl;


    return 0;
}