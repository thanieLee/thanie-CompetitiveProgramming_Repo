alphabet = "abcdefghijklmnopqrstuvwxyz"

class Node(object):
    """
    A single node of a trie.
    
    Children of nodes are defined in a dictionary
    where each (key, value) pair is in the form of
    (Node.key, Node() object).
    """
    def __init__(self, key, data=None):
        self.key = key
        self.data = data # data is set to None if node is not the final char of string
        self.isEnd = False
        self.children = {}
        
class Trie(object):
    """
    A simple Trie with insert, search, and starts_with methods.
    """
    def __init__(self):
        self.head = Node(None)
    
    """
    Inserts string in the trie.
    """
    def insert(self, string):
        curr_node = self.head
        
        for char in string:
            if char not in curr_node.children:
                curr_node.children[char] = Node(char)
                
            curr_node = curr_node.children[char]
            
        # When we have reached the end of the string, set the curr_node's data to string.
        # This also denotes that curr_node represents the final character of string.
        curr_node.data = string
    
    
    """
    Returns if string exists in the trie
    """
    def search(self, string):
        curr_node = self.head
        
        for char in string:
            if char in curr_node.children:
                curr_node = curr_node.children[char]
            else:
                return False
            
        # Reached the end of string,
        # If curr_node has data (i.e. curr_node is not None), string exists in the trie
        if (curr_node.data != None):
            return True
    
    """
    Returns a list of words in the trie
    that starts with the given prefix.
    """
    def starts_with(self, prefix):
        curr_node = self.head
        result = []
        subtrie = None
        
        # Locate the prefix in the trie,
        # and make subtrie point to prefix's last character Node
        for char in prefix:
            if char in curr_node.children:
                curr_node = curr_node.children[char]
                subtrie = curr_node
            else:
                return None
            
        # Using BFS, traverse through the prefix subtrie,
        # and look for nodes with non-null data fields.
        queue = list(subtrie.children.values())
        
        while queue:
            curr = queue.pop()
            if curr.data != None:
                result.append(curr.data)
            
            queue += list(curr.children.values())
                
        return result



def VigenereCipher(key, word):
    output = ""
    key = key.lower()
    word = word.lower()
    for i in range(len(word)):
        keyVal = alphabet.find(key[(i)%len(key)])
        wordVal = alphabet.find(word[(i)])
        output += alphabet[(keyVal+wordVal)%26]

    return output        
t = Trie()

file = open("EnglishWords.txt", "r")
words = file.readlines()

def VigenereDecipher(keyGuess, cipher):
    guess = ""
    for i in range(len(cipher)):
        keyGuessVal = alphabet.find(keyGuess[i%len(keyGuess)])
        cipherVal = alphabet.find(cipher[i])
        guess += alphabet[(cipherVal-keyGuessVal)%26]
    return guess

possibleKeys = []
def VigenereDecipherBruteForce(keyLen, cipher, cur=""):
    if len(cur) == keyLen:
        word = VigenereDecipher(cur, cipher)
        curNode = t.head
        charCnt = 0
        for char in word:
            if char not in curNode.children:
                break
            curNode = curNode.children[char]
            if curNode.data != None and charCnt > 5:
                possibleKeys.append(cur) 
            charCnt += 1
    else:
        for i in range(26):
            cur1 = (cur + '.')[:-1]
            cur1 += alphabet[i]
            VigenereDecipherBruteForce(keyLen, cipher, cur1)

cnt = 0
for word in words:
    word = word.strip()
    t.insert(word)

print(VigenereCipher("math", "cryptographyissupercool"))
#print(VigenereDecipherBruteForce(4, VigenereCipher("math", "cryptographyissupercool")))
#print(*possibleKeys)


