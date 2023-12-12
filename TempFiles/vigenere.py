from collections import defaultdict
alphabet = "abcdefghijklmnopqrstuvwxyz"
def VigenereCipher(key, word):
    output = ""
    key = key.lower()
    word = word.lower()
    for i in range(len(word)):
        if word[i] not in alphabet:
            output += word[i]
            continue
        keyVal = alphabet.find(key[(i)%len(key)])
        wordVal = alphabet.find(word[(i)])
        output += alphabet[(keyVal+wordVal)%26]

    return output        

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



def IndexOfCoincidence(text, period):
    cnt = 0
    freq = defaultdict(int)
    n = 0
    for char in text:
        if char in alphabet:
            n += 1
    check = 0
    for i in range(0, len(text), period):
        if text[i] not in alphabet:
            continue
        freq[text[i]] += 1
        check += 1
    

    for key, val in freq.items():
        cnt += (val * val-1)
    
    return cnt  / ((check * (check-1)))


def FindKeywordLen(cur):
    ans = 0
    cnt = 100000
    engIC = 0.06667
    for i in range(1, 11):
        ic = IndexOfCoincidence(cur, i)
        if abs(ic - engIC) < cnt:
            ans = i
            cnt = abs(ic - engIC)
    return ans

def clearText(t):
    t = t.replace(" ", "")
    t = t.replace(",", "")
    t = t.replace(".", "")
    t = t.lower()
    return t

def keyElim(keyLen, probWord, cipher):
    if len(probWord) < keyLen+1:
        return "probable guess not long enough"
    cipherShift = (cipher + '.')[:-1]
    for i in range(keyLen):
        cipherShift = cipherShift[1:]
    
    newShift = ""
    print(cipher[:20])
    print(cipherShift[:20])
    for i in range(len(cipherShift)):
        shiftVal = alphabet.find(cipherShift[i])
        origVal = alphabet.find(cipher[i])
        newShift += alphabet[(origVal - shiftVal)%26]
    
    print(newShift[:20])
    shiftedWord = (probWord + '.')[:-1]
    for i in range(keyLen):
        shiftedWord = shiftedWord[1:]
    wordShift = ""
    for i in range(len(shiftedWord)):
        shiftVal = alphabet.find(shiftedWord[i])
        origVal = alphabet.find(probWord[i])
        wordShift += alphabet[(origVal - shiftVal)%26]

    print(wordShift[:5])
    index = newShift.find(wordShift)
    if index == -1:
        return "Cannot find key"

    key = [""] * keyLen
    for i in range(keyLen):
        cipherVal = alphabet.find(cipher[i+index])
        plainVal = alphabet.find(probWord[i])
        key[(i+index)%keyLen] = alphabet[(cipherVal-plainVal)%26]
    keyStr = ""
    for char in key:
        keyStr += char
    return keyStr

test = "a love letter to number theory: There was a time when he would have embraced the change that was coming. In his youth, he sought adventure and the unknown, but that had been years ago. He wished he could go back and learn to find the excitement that came with change but it was useless. That curiosity had long left him to where he had come to loathe anything that put him out of his comfort zone. If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out."
#test = "numbertheoryisoneofthemostinterestingsubjects"
test = clearText(test)
cur = VigenereCipher("prime", test)
print(cur[:25])

print(keyElim(5, "loveletter", cur))
#print(VigenereDecipherBruteForce(4, VigenereCipher("math", "cryptographyissupercool")))
#print(*possibleKeys)















"""for word in words:
    word = word.strip()
    t.insert(word)"""