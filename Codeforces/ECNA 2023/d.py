arr = [int(i) for i in input().split()]
cnt = 0
for i in range(0, 10, 2):
    cnt += arr[i]*arr[i+1]
n, kwf = [int(i) for i in input().split()]
cnt = cnt//5

print(int((n*cnt)//kwf))