#include <bits/stdc++.h>
using namespace std;

struct node {
    char letter;
    int endCnt = 0;
    vector<node> children = {};
    node *parent;

    node(char c){
        letter = c;
        parent = new node();
    }

    node(){
        letter = ' ';
        
    }
};

void addNode(node &par, char n, bool isEnd){
    node child = node(n);
    par.children.push_back(child);
    child.parent = &par;
    if (isEnd){
        child.endCnt++;
        node& cur = par;
        while (cur.letter != ' '){
            //cout << "test" << " " << cur.letter << " " << n << endl;
            cur.endCnt++;
            //cout << "huh" << cur.parent->letter << "e"<< endl;
            cur = *(cur.parent);
        }
        //cout << "damn" << endl;
    }
}

node findChild(node &par, char n){
    node temp = node();
    node &ans = temp;
    for (node &child : par.children){
        cout << child.letter << " " << n << endl;
        if (child.letter == n){
            ans = (child);
        }
    }
    //cout << ans.letter << " haha" <<endl;
    return ans;
}


int main(){
    int n; cin >> n;
    node start(' ');

    for (int i = 0; i < n; i++){
        string q; cin >> q;
        node &cur = start;
        if (q == "add"){
            string s; cin >> s;
            for (int i = 0; i < s.size(); i++){
                bool end = false;
                if (i == s.size()-1) end = true;
                cout << cur.letter << endl;
                if (findChild(cur, s[i]).letter == ' '){
                    cout << "wut" << findChild(cur, s[i]).letter << "t" <<  endl;
                    addNode(cur, s[i], end);
                }

                cur = findChild(cur, s[i]);
            }
        }
    }
}