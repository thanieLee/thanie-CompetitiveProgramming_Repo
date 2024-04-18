arr1 = []
arr2 = []
for i in range(292):
    x = int(input())
    arr1.append(x)

for i in range(291):
    x = int(input())
    arr2.append(x)

for num in arr1:
    if num not in arr2:
        print(num)