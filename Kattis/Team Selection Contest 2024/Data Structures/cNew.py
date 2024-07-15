n = int(input())
a = [int(i) for i in input().split()]
nodes = []

"""if n == 1:
    print(0)
    print(*a)
    exit()
"""

class Node:
    def __init__(self) -> None:
        self.nex = None
        self.prev = None
        self.idx = None
    
for i in range(n):
    cur_node = Node()
    cur_node.idx = i
    nodes.append(cur_node)

for i in range(n):
    cur_node = nodes[i]
    if i == 0:
        cur_node.nex = nodes[i+1]
    elif i == n-1:
        cur_node.prev = nodes[i-1]
    else:
        cur_node.nex = nodes[i+1]
        cur_node.prev = nodes[i-1]

nodes_to_check = [int(i) for i in range(n)]
active = [True for i in range(n)]
ans = []
while len(nodes_to_check) > 0:

    to_check = set()
    removed = []

    for i in range(len(nodes_to_check)):
        cur_node = nodes[nodes_to_check[i]]
        can = True
        prev_node = cur_node.prev
        next_node = cur_node.nex
        
        if prev_node != None:
            if a[prev_node.idx] > a[cur_node.idx]:
                can = False

        if next_node != None:
            if a[next_node.idx] > a[cur_node.idx]:
                can = False 
        
        if not can:
            removed.append(cur_node.idx)

    for i in range(len(removed)):
        cur_node = nodes[removed[i]]
        prev_node = cur_node.prev
        next_node = cur_node.nex
        
        active[cur_node.idx] = False

        if cur_node.idx in to_check:
            to_check.remove(cur_node.idx)
        
        if prev_node != None:
            prev_node.nex = cur_node.nex
            to_check.add(prev_node.idx)
        if next_node != None:
            next_node.prev = cur_node.prev
            to_check.add(next_node.idx)

    nodes_to_check = sorted(list(to_check))
    ans.append(removed)

print(len(ans)-1)    
for i in range(len(ans)):
    an = ans[i]
    for i in an:
        print(a[i], end=" ")
    if i != len(ans)-1:
        print()

for i in range(n):
    if active[i]:
        print(a[i], end=" ")


        
