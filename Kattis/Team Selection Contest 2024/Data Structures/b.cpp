#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;



struct segtree_coach {
    vector<pll> t;
    int n;
    segtree_coach(vector<pll> &a, int n) : n(n) {
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }

    void build(vector<pll> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            pull(v);
        }
    }

    void pull(int v) {
        t[v] = max(t[v*2], t[v*2+1]);
    }

    void update(int v, int tl, int tr, int pos, pll val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, val);
            else
                update(v*2+1, tm+1, tr, pos, val);
            pull(v);
        }
    }

    pll query(int v, int tl, int tr, int l, int r)
    {
        if (l > r)
            return {0, -1};
        if (l == tl and r == tr)
            return t[v];
        int tm = (tl + tr) / 2;

        return max(query(v*2, tl, tm, l, min(r, tm)), query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
};


int main(){
    int n, k; cin >> n >> k;
    vector<segtree_coach> coach_pref;
    map<string, int> players;
    vector<string> player_names;

    vector<vector<string>> coach_names;

    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        vector<string> prefs;
        for (int i = 0; i < p; i++) {
            string s; cin >> s;
            prefs.push_back(s);
        }
        coach_names.push_back(prefs);
    }

    int p; cin >> p;
    set<int> players_left;
    for (int i = 0; i < p; i++) {
        string s; cin >> s;
        players[s] =  i;
        players_left.insert(i);
        player_names.push_back(s);
    }

    for (int i = 0; i < n; i++) {
        vector<pll> cur_coach(p);
        for (int j = 0; j < p; j++) {
            cur_coach[i] = {0, i};
        }
        int mx = p+10;
        for (int j = 0; j < coach_names[i].size(); j++) {
            int cur_player = players[coach_names[i][j]];
            cur_coach[cur_player] = {mx, cur_player};
            mx--;
        }

        segtree_coach cur_coach_tree(cur_coach, p);
        coach_pref.push_back(cur_coach_tree);
    }

    int decide_coach = 0;
    vector<vector<string>> coach_choices(n, vector<string>());
    for (int i = 0; i < n*k; i++) {
        pll search = coach_pref[decide_coach].query(1, 0, p-1, 0, p-1);

        if (search.first != 0) {
            coach_choices[decide_coach].push_back(player_names[search.second]);
            for (int j = 0; j < n; j++) {
                coach_pref[j].update(1, 0, p-1, search.second, {0, -1});
            }
            players_left.erase(players_left.find(search.second));
        } else {
            int next = *players_left.begin();
            coach_choices[decide_coach].push_back(player_names[next]);
            for (int j = 0; j < n; j++) {
                coach_pref[j].update(1, 0, p-1, next, {0, -1});
            }
            players_left.erase(players_left.find(next));
        }

        decide_coach++;
        decide_coach %= n;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < coach_choices[i].size(); j++) {
            cout << coach_choices[i][j] << " ";
        }
        cout << endl;
    }
}