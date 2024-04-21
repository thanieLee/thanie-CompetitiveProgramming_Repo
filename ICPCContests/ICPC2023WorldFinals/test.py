import sys
from math import ceil

def det3(A):
    a = A[0][0]
    b = A[0][1]
    c = A[0][2]
    d = A[1][0]
    e = A[1][1]
    f = A[1][2]
    g = A[2][0]
    h = A[2][1]
    i = A[2][2]
    
    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g)

def det2(A):
    a = A[0][0]
    b = A[0][1]
    c = A[1][0]
    d = A[1][1]

    
    return a*d-b*c


def inv(A):
    transA = [[0 for i in range(3)] for j in range(3)]
    for i in range(3):
        for j in range(3):
            transA[i][j] = A[j][i]
    
    adjA = [[0 for i in range(3)] for j in range(3)]
    sign = [[1, -1, 1], [-1, 1, -1], [1, -1, 1]]
    for i in range(3):
        for j in range(3):
            cnt = 0
            curMatrix = [[0 for i in range(2)] for j in range(2)]
            for k in range(3):
                for l in range(3):
                    if i == k or j == l: continue
                    curMatrix[cnt//2][cnt%2] = transA[k][l]
                    cnt += 1
            
            adjA[i][j] = det2(curMatrix)
    
    ans = [[0 for i in range(3)] for j in range(3)]
    deter = det3(A)
    for i in range(3):
        for j in range(3):
            ans[i][j] = sign[i][j]*adjA[i][j]/deter
    
    return ans

def mul(A, v):
    ans = [0, 0, 0]
    for i in range(3):
        ans[i] = ceil(A[i][0]*v[0] + A[i][1]*v[1] + A[i][2]*v[2])
    return ans

def same(v1, v2):
    return v1[0]==v2[0] and v1[1]==v2[1] and v1[2]==v2[2]


rows = [[1, 3, 5], [1, 3, 7], [2, 1, 8], [5, 6, 7], [3, 1, 4]]
temp = [[1, 2, 3], [0, 1, 4], [5, 6, 0]]
ans = []
for i in range(5):
    print(rows[i][0], rows[i][1], rows[i][2])
    sys.stdout.flush()
    x = int(input())
    ans.append(x)

vectors = []
for i in range(5):
    for j in range(i+1, 5):
        for k in range(j+1, 5):
            mat = []
            mat.append(rows[i])
            mat.append(rows[j])
            mat.append(rows[k])
            matInv = inv(mat)
            vec = [ans[i], ans[j], ans[k]]
            an = mul(matInv, vec)
            vectors.append(an)

for i in range(len(vectors)):
    cur = vectors[i]
    cnt = 0
    for j in range(len(vectors)):
        if i == j: continue
        nex = vectors[j]
        if cur[0]==nex[0] and cur[1]==nex[1] and cur[2]==nex[2]:
            cnt += 1
    if cnt >= 3:
        print(cur[0], cur[1], cur[2])
        exit()
