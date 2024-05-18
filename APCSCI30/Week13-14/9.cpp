#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct Node {
    char c;
    map<char, Node> childDict;

    Node(char c1) {
        c = c1;
    }

    void addChild(char c1){
        if (childDict.find(c1) == childDict.end()) {
            Node newNode(c1);
            childDict[c1] = newNode;
        }
    }
};

struct Trie {
    Node* rootNode;

    Trie (Node* root) {
        rootNode = root;
    }
    
};

int main(){
    
}