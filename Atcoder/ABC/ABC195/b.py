a, b, w = [int(i) for i in input().split()]
w*=1000
mn = -1
mx = -1

for i in range(1, 1000001):
    if a*i <= w <= b*i:
        if mn == -1:
            mn = i
        mx = i

if mn == -1:
    print("UNSATISFIABLE")
else:
    print(mn, mx)
