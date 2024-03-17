from itertools import permutations as perm
d = int(input())

def isValidOp(arrOp):
    hasValid = False
    
    for op in arrOp:
        if op == '+' or op == '-':
            hasValid = True
        elif hasValid and (op == '*' or op == '/'):
            return False
        
    return True


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
    return did

def isValid2(x, y, z, op1, op2, d):
    did = False
    for per in perm([x, y, z]):
        did |= opVal(per[0], per[1], op1) == d or opVal(per[0], per[1], op2) == d
        did |= opVal(per[0], per[2], op1) == d or opVal(per[0], per[2], op2) == d
        did |= opVal(per[2], per[1], op1) == d or opVal(per[2], per[1], op2) == d
    return did

ops = ['+', '-', '*', '/']
for d in range(1, 101):
    exit = False
    for i in range(1, 100):
        for j in range(1, 100):
            for k in range(1, 100):
                if i == j or j == k or i == k or i == d or j == d or k == d:
                    continue
                

                
                can = False
        
                for l in range(4):
                    for m in range(4):
                        if isValid(i, j, k, ops[l], ops[m], d) or isValid2(i, j, k, ops[l], ops[m], d):
                            can = True

                
                
                if not can:
                    print(d, i, j, k)
                    exit = True
                    break
            if exit:
                break
        if exit:
            break


                
                
            