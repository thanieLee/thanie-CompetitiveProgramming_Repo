from math import log2,ceil
n=int(input())
test = bin(n)[2:]

add = False
for i in range(1, len(test)):
    if test[i] == '1':
        add = True

if add:
    print(len(test)+1)
else:
    print(len(test))

print(float(2**59+1))
print(log2(float(2**59+1)))