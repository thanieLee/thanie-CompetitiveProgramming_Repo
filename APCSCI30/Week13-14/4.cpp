#include <bits/stdc++.h>
using namespace std;
using namespace std;
struct TrieNode
{
	map<char,TrieNode*> children;
	int prefixes;
	bool endofword;
	TrieNode()
	{
		prefixes=0;
		endofword=false;
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
	current->endofword=true;
}
bool search(TrieNode *root,string word)
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
    TrieNode *root=new TrieNode();
    vector<int> ans;
    for (int i = 0; i < n; i++){
        string q; cin >> q;
        if (q == "add"){
            string s; cin >> s;
            insert(root, s);
        } else {
            string s; cin >> s;
            ans.push_back(count_prefix(root, s));
        }
    }
}