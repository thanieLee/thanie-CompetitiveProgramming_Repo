#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    char ch;
    unordered_map<char, Node*> children;
    vector<int> indexes; //store the indexes of the substring from where it starts
    Node(char c):ch(c){}
};

int maxLen = 0;
string maxStr = "";

void insertInSuffixTree(Node* root, string str, int index, string originalSuffix, int level=0)
{
    root->indexes.push_back(index);

    // it is repeated and length is greater than maxLen
    // then store the substring
    if(root->indexes.size() > 1 && maxLen < level)
    {
        maxLen = level;
        maxStr = originalSuffix.substr(0, level);
    }

    if(str.empty()) return;

    Node* child;
    if(root->children.count(str[0]) == 0) {
        child = new Node(str[0]);
        root->children[str[0]] = child;
    } else {
        child = root->children[str[0]];
    }

    insertInSuffixTree(child, str.substr(1), index, originalSuffix, level+1);
}

int main()
{
    string str; cin >> str;
    Node* root = new  Node('@');

    //insert all substring in suffix tree
    for(int i=0; i<str.size(); i++){
        string s = str.substr(i);
        insertInSuffixTree(root, s, i, s);
    }
    if (maxLen > 0)
        cout << maxStr << endl;
    else
        cout << -1 << endl;

    return 1;
}

