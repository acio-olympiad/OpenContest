import tree_gen as tg
import sys
import random

N, M, tree_type, id_type = map(int, sys.argv[1:])

tree = tg.TREE_TYPES[tree_type](N)

ids = tg.ID_TYPES[id_type](2,N+1) + [1]
tg.assign_ids(tree, ids)

parent = [0]*(N+1)
def dfs(u):
    stack = [(u,0)]
    while stack:
        u,i = stack.pop()
        if i < len(u.child):
            stack.append((u,i+1)) 
            stack.append((u.child[i], 0))
            parent[u.child[i].id] = u.id             

dfs(tree)

print(N,M)
print(*[random.randint(1, int(1e6)) for i in range(N)])
print(*[random.randint(1, int(1e6)) for i in range(M)])
print(*parent[2:])
