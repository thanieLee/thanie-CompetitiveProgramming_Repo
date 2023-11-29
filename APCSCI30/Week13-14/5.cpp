#include <bits/stdc++.h>
using namespace std;
struct TrieNode
{
    map<char,TrieNode*> children;
    int prefixes;
    int endofword;
    TrieNode()
    {
        prefixes=0;
        endofword=0;
    }
};
void insert(TrieNode *root,string word)
{
    TrieNode *current=root;
    for(int i=0;i<word.size();i++)
    {
        char ch=word[i];
        TrieNode *node=current->children[ch];
        if(!node)
        {
            node=new TrieNode();
            current->children[word[i]]=node;
        }
        current=node;
        current->prefixes++;
    }
    current->endofword++;
}
int search(TrieNode *root,string word)
{
    TrieNode *current=root;
    for(int i=0;i<word.size();i++)
    {
        char ch=word[i];
        TrieNode *node=current->children[ch];
        if(!node)
            return false;
        current=node;
    }
    return current->endofword;
}

string prefSearch(TrieNode *root,string word)
{
    TrieNode *current=root;
    string out = "";
    for(int i=0;i<word.size();i++)
    {
        char ch=word[i];
        out += ch;
        TrieNode *node=current->children[ch];
        if(current->endofword)
            return out;
        current=node;
    }
    if (current->endofword > 1)
        return "z";
    return out;
}


int count_prefix(TrieNode *root,string word)
{
    TrieNode *current=root;
    for(int i=0;i<word.size();i++)
    {
        char ch=word[i];
        TrieNode *node=current->children[ch];
        if(!node)
        {
            return 0;
        }
        current=node;
    }
    return current->prefixes;
}

int main(){
    int n; cin >> n;
    vector<string> arr;
    TrieNode *root=new TrieNode();

    for (int i = 0; i < n; i++){
        string s; cin >> s;
        arr.push_back(s);
    }

    for (string s : arr){
        insert(root, s);
    }

    for (string s : arr){
        string temp = prefSearch(root, s);
        if (temp != s){
            cout << "BAD SET" << endl;
            cout << s << endl;
            return 0;
        }
    }
    cout << "GOOD SET" << endl;
}
