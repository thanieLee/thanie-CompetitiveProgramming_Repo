n = str(input())

ans = 0
for i in range(len(n)-1):
    if i < 3: continue
    ans += ((i)//3)*(pow(10, i+1)-pow(10, i))
ans += ((len(n)-1)//3)*(int(n)-pow(10, len(n)-1)+1)
print(ans)
