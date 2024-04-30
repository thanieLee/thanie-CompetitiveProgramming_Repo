t = int(input())

while t>0:
    t-=1
    n = int(input())
    s = input()
    cnt = 0
    for i in range(n):
        if s[i] == "U":
            cnt += 1
    
    if cnt%2 == 0:
        print("NO")
    else:
        print("YES")
    