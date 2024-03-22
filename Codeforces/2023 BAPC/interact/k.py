import sys
n = int(input())
deltax = [-1, 1, 0, 0]
deltay = [0, 0, -1, 1]

def valid(curx, cury, dir):
    return 0 < curx+deltax[dir] and curx+deltax[dir] <= n and 0 < cury+deltay[dir] and cury+deltay[dir] <= n

def newp(curx, cury, dir):
    return [curx+deltax[dir] , cury+deltay[dir]]

xl = 1
xr = n
yl = 1
yr = n
vertprev = -1
horizprev = -1

while xl != xr and yl != yr:
    xmid = xl + (xr-xl)//2
    ymid = yl + (yr-yl)//2

    vertcur = -1
    horizcur = -1
    vertmx = 0
    horizmx = 0

    for i in range(yl, yr+1):
        print("?", xmid, i)
        sys.stdout.flush()
        curheight = int(input())
        if curheight > vertmx:
            vertmx = curheight
            vertcur = i
    
    for i in range(xl, xr+1):
        print("?", i, ymid)
        sys.stdout.flush()
        curheight = int(input())
        if curheight > horizmx:
            horizmx = curheight
            horizcur = i
    
    left = -1
    right = -1
    top = -1
    bottom = -1

    if valid(xmid, vertcur, 0):
        ne = newp(xmid, vertcur, 0)
        print("?", ne[0], ne[1])
        sys.stdout.flush()
        left = int(input())
        
    
    if valid(xmid, vertcur, 1):
        ne = newp(xmid, vertcur, 1)
        print("?", ne[0], ne[1])
        sys.stdout.flush()
        right = int(input())
    
    if valid(horizcur, ymid, 2):
        ne = newp(horizcur, ymid, 2)
        print("?", ne[0], ne[1])
        sys.stdout.flush()
        top = int(input())
    
    if valid(horizcur, ymid, 3):
        ne = newp(horizcur, ymid, 3)
        print("?", ne[0], ne[1])
        sys.stdout.flush()
        bottom = int(input())
    
    
    didvert = False
    didhoriz = False
    if left != -1:
        if left > vertprev and left > right:
            vertprev = left
            xr = xmid
            didvert = True
    
    if right != -1:
        if right > vertprev and right > left:
            vertprev = right
            xl = xmid
            didvert = True
    
    if top != -1:
        if top > horizprev and top > bottom:
            horizprev = top
            yr = ymid
            didhoriz = True
    
    if bottom != -1:
        if bottom > horizprev and bottom > top:
            horizprev = bottom
            yl = ymid
            didhoriz = True
    
    if not didvert:
        yl = ymid
        yr = ymid
    
    if not didhoriz:
        xl = xmid
        xr = xmid


print("?", xl, yl)
sys.stdout.flush()
print("!", max(int(input()), vertprev, horizprev))
    
    

    
    