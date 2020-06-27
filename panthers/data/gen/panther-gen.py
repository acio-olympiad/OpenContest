import treegen as tg
import sys
import random

usage = """
Usage:
To generate a random case for a subtask use:
python panther-gen.py <subtask>

To specify additional parameters, use:
python panther-gen.py <subtask> <N> <treetype> <idtype>

case will be written to stdout

subtask - the subtask of case (1-5)
N - number of cities (1 - subtask limit)
treetype - the type of tree generated as per treegen.py (0-9)
idtype - the ordering of ids assigned to the tree as per treegen.py (0-2)
"""

SUBTASKS = 5
ARGS = 4

if len(sys.argv) < 2:
    print(usage)

if len(sys.argv) < ARGS + 1:
    subtask = int(sys.argv[1])
else:
    subtask, N, tree_type, id_type = map(int, sys.argv[1:])

if subtask < 1 or subtask > SUBTASKS:
    raise Exception("Invalid subtask number.")

defaults = (1000, list(range(len(tg.TREE_TYPES))), list(range(len(tg.ID_TYPES))))

MAX_N, allowed_trees, allowed_ids = (
    (), # 1-based subtasks,
    (200, defaults[1], defaults[2]),
    (1000, [0], defaults[2]),
    (1000, defaults[0], [2]),
    (600, defaults[1], defaults[2]),
    defaults
)[subtask]

# if constraints are not specified, will generate them randomly
if len(sys.argv) < ARGS + 1:
    N = random.randint(2, MAX_N)
    tree_type = random.choice(allowed_trees)
    id_type = random.choice(allowed_ids)

# checks if valid
if N < 1 or N > MAX_N:
    raise Exception("N out of bounds for subtask.")

if  tree_type not in allowed_trees:
    raise Exception("Invalid tree type for subtask.")

if  id_type not in allowed_ids:
    raise Exception("Invalid id type for subtask.")

tree = tg.TREE_TYPES[tree_type](N)

ids = tg.ID_TYPES[id_type](0,N)
tg.assign_ids(tree, ids)

parent = [-1]*N
def dfs(u):
    stack = [(u,0)]
    while stack:
        u,i = stack.pop()
        if i < len(u.child):
            stack.append((u,i+1)) 
            stack.append((u.child[i], 0))
            parent[u.child[i].id] = u.id

dfs(tree)

print(N,subtask)
print(*parent)
