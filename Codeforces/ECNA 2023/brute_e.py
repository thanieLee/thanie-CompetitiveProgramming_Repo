from math import log2
def C(n):
    if n%2 == 0:
        return n//2
    else:
        return 3*n+1

def CS(n):
    cur = n
    output = ""
    while pow(2, int(log2(cur))) != cur:
        if cur % 2 == 0:
            output += "E"
        else:
            output += "O"
        cur = C(cur)
    
    return output

test = {}
for i in range(5, 10000):
    if CS(i) not in test:
        test[CS(i)] = i
        print(CS(i), i)
    else:
        print(CS(i), test[CS(i)])