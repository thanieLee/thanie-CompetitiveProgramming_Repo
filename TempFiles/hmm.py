import sys
n, m = [int(i) for i in input().split()]
tree = [[i for i in range(m)]] * (4 * n); 
def permMult(A, B):
    global m
    ans = [i for i in range(m)]
    for i in range(m):
        ans[i] = A[B[i]]
    return ans

def build(arr, v, tl, tr):
    if (tl == tr):
        tree[v] = arr[tl];
    else:
        tm = (tl + tr) // 2
        build(arr, v*2, tl, tm)
        build(arr, v*2+1, tm+1, tr)
        
        pull(v)

def pull(v):
    tree[v] = permMult(tree[v*2], tree[v*2+1])
        
def updateTreeNode(v, tl, tr, pos, newPerm) : 
    if tl == tr:
        tree[v] = newPerm
    else:
        tm = (tl + tr) // 2
        if (pos <= tm):
            updateTreeNode(v*2, tl , tm, pos, newPerm)
        else:
            updateTreeNode(v*2+1, tm+1, tr, pos, newPerm)
        pull(v)
        
        
def query(v, tl ,tr, l, r) : 
    if l > r:
        return [i for i in range(m)]
    if(l <= tl and tr <= r):
        return tree[v]

    tm = (tl + tr) // 2
    
    ans = permMult(query(v*2, tl, tm, l ,min(r, tm)), query(2*v+1, tm+1, tr, max(l, tm+1), r))
    return ans

input = sys.stdin.readline
print = sys.stdout.write
curPerm = [int(i)-1 for i in input().split()]
arr = []
for i in range(n):
    nextPerm = [i for i in range(m)]
    a, b = [int(i) for i in input().split()]
    a -= 1
    b -= 1
    nextPerm[a] = b
    nextPerm[b] = a
    arr.append(nextPerm)

build(arr, 1, 0, n-1)
q = int(input())
for i in range(q):
    quer = [str(i) for i in input().split()]
    if quer[0] == "PERM":
        l, r = [int(quer[1]), int(quer[2])]
        l -= 1
        r -= 1
        ans = permMult(curPerm, query(1, 0, n-1, l, r))
        for i in range(m):
            ans[i] += 1
            print(f"{ans[i]} ")
        print("\n")
    else:
        x, a, b = [int(quer[1]), int(quer[2]), int(quer[3])]
        x -= 1
        a -= 1
        b -= 1
        nextPerm = [i for i in range(m)]
        nextPerm[a] = b
        nextPerm[b] = a
        updateTreeNode(1, 0, n-1, x, nextPerm)