import tree_gen as tg
import sys
import random

usage = """
Usage:
To generate a random case for a subtask use:
python vibe-gen.py <subtask>

To specify additional parameters, use:
python vibe-gen.py <subtask> <N> <M> <treetype>

case will be written to stdout

subtask - the subtask of case (1-6)
N - number of cities (2 - subtask limit)
M - number of reporters (1 - subtask limit)
treetype - the type of tree generated as per tree_gen.py (0-9)
"""

if len(sys.argv) < 2:
    print(usage)

if len(sys.argv) < 6:
    subtask = int(sys.argv[1])
else:
    subtask, N, M, tree_type = map(int, sys.argv[1:])

defaults = (int(1e5), int(1e6), int(1e6), list(range(len(tg.TREE_TYPES))))

# if constraints are not specified, will generate them randomly

MAX_N, MAX_M, MAX_di, allowed_types = (
    (), # 1-based subtasks,
    (100, defaults[1], 100, defaults[3]),
    (1000, defaults[1], 1000, defaults[3]),
    (defaults[0], 1, defaults[2], [0]),
    (defaults[0], 1, defaults[2], defaults[3]),
    (defaults[0], defaults[1], defaults[2], [0]),
    defaults
)[subtask]

MAX_vi = int(1e6)

if len(sys.argv) < 6:
    N = random.randint(2, MAX_N)
    M = random.randint(1, MAX_M)
    tree_type = random.choice(allowed_types)

id_type = 2

# checks if valid subtask
if N < 2 or N > MAX_N:
    raise Exception("N out of bounds for subtask.")

if M < 1 or M > MAX_M:
    raise Exception("M out of bounds for subtask.")

if  tree_type not in allowed_types:
    raise Exception("Invalid tree type for subtask.")

if id_type != 2:
    raise Exception("id type must == 2 to maintain a_i < i constraint.")

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
print(*[random.randint(1, int(MAX_vi)) for i in range(N)])
print(*[random.randint(1, int(MAX_di)) for i in range(M)])
print(*parent[2:])
