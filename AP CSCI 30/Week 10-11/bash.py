arr1 = []
arr2 = []

f1 = open("output.txt", "r")

for x in f1:
    arr1.append(x)

f2 = open("test_output (3).txt", "r")

for x in f2:
    arr2.append(x)

for i in range(len(arr1)):
    if arr1[i] != arr2[i]:
        print(i+1, arr1[i], arr2[i])