from collections import defaultdict


nodes_to_check = []
all_nodes = []

class Node():
    
    def __init__(self, val, idx):
        self.val = val
        self.idx = idx
        self.nex = None
        self.prev = None


class linked_list():
    def __init__(self):
        self.head = None
        self.tail = None


    def remove_node(self, node_idxs):
        cur = self.head

        for node, to_remove in node_idxs.items():
            cur = all_nodes[node]
            if to_remove:
                if cur == self.head:
                    self.head = self.head.nex
                    cur = self.head
                    self.head.prev = None
                elif cur == self.tail:
                    self.tail = self.tail.prev
                    cur = None
                    self.tail.nex = None
                else:
                    bef = cur.prev
                    aft = cur.nex
                    bef.nex = aft
                    aft.prev = bef
                    cur = aft
            else:
                cur = cur.nex

    def print_list(self):
        cur = self.head
        out = []
        while cur != None:
            out.append(cur.val)
            cur = cur.nex
        
        return out
    
    def add_node(self, new_node):

        if self.head == None and self.tail == None:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.nex = new_node
            new_node.prev = self.tail
            self.tail = new_node

    def remove_map(self):
        remove = defaultdict(bool)
        if len(nodes_to_check) == 0:
            cur = self.head
            while cur != None:
                can = True
                if cur.prev != None:
                    if cur.prev.val > cur.val:
                        can = False
                        if cur.nex != None:
                            nodes_to_check.append(cur.nex.idx)
                
                if cur.nex != None:
                    if cur.nex.val > cur.val:
                        can = False
                        if cur.prev != None:
                            nodes_to_check.append(cur.prev.idx)

                
                if not can:
                    remove[cur.idx] = True

                cur = cur.nex
        else:
            for idx in nodes_to_check:
                cur = all_nodes[idx]
                can = True
                if cur.prev != None:
                    if cur.prev.val > cur.val:
                        can = False
                        if cur.nex != None:
                            nodes_to_check.append(cur.nex.idx)
                
                if cur.nex != None:
                    if cur.nex.val > cur.val:
                        can = False
                        if cur.prev != None:
                            if not remove[cur.prev.idx]:
                                nodes_to_check.append(cur.prev.idx)

                
                if not can:
                    remove[cur.idx] = True

        return remove



n = int(input())
a = [int(i) for i in input().split()]

ll = linked_list()

for i in range(n):
    new_node = Node(a[i], i)
    ll.add_node(new_node)
    all_nodes.append(new_node)

test = ll.remove_map()

remove_count = 1

ans = []
while remove_count != 0:
    print(*nodes_to_check)
    remove = ll.remove_map()
    remove_count = 0
    cur = []
    for i, j in remove.items():
        cur.append(a[i])
        remove_count += 1

    if remove_count == 0:
        ans.append(ll.print_list())
    else:
        ans.append(cur)

    ll.remove_node(remove)
    nodes_to_check = []

print(len(ans)-1)

for cnt in ans:
    print(*cnt)