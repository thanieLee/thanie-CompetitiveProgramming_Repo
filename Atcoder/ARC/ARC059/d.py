from math import *

s = str(input())
alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
cnt = [[] for _ in range(26)]

for i in range(len(s)):
    cnt[alpha.find(s[i])].append(i)

for i in range(26):
    currentLetter = cnt[i]
    for j in range(len(currentLetter)):
        for k in range(j+1, len(currentLetter)):
            if (k-j+1) > floor((currentLetter[k]-currentLetter[j])/2)+1:
                print(currentLetter[j]+1, currentLetter[k]+1)
                exit()

print(-1, -1)