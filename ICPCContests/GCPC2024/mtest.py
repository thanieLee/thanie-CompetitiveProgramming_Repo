from itertools import permutations as perm
d = int(input())
if d < 10:
    print(99, 55, 77)
else:
    print(1, 2, 3)

def opVal(x, y, op):
    if op == '+':
        return x+y
    elif op == '-':
        return x-y
    elif op == '*':
        return x*y
    else:
        return x/y

def isValid(x, y, z, op1, op2, d):
    did = False
    for per in perm([x, y, z]):
        did |= opVal(opVal(per[0], per[1], op1), per[2], op2) == d
        print(opVal(opVal(per[0], per[1], op1), per[2], op2), per[0], per[1], per[2], op1, op2)
    return did

ops = ['+', '-', '*', '/']
can = False
for l in range(4):
    for m in range(4):
        can |= isValid(9, 5, 17, ops[l], ops[m], 2)
print(can)
