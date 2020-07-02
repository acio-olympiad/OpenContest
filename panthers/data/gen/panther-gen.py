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

subtask - the subtask of case (1-4)
N - number of cities (1 - subtask limit)
treetype - the type of tree generated as per treegen.py (0-12)
idtype - the ordering of ids assigned to the tree as per treegen.py (0-2)
"""

SUBTASKS = 4
ARGS = 6

if len(sys.argv) < 3:
    print(usage)

grader_type, subtask = map(int,sys.argv[1:3])

INPUT_TREE, ADV_SPIKEY, ADV_INPUT_TREE = range(3)

if grader_type == ADV_SPIKEY:
    # note: no checks run for ADV_SPIKEY
    N, spikes = sys.argv[3:]
    print(ADV_SPIKEY, N, subtask)
    print(spikes)
else:
    if len(sys.argv) >= ARGS:
        N, tree_type, id_type = map(int, sys.argv[3:])

    if subtask < 1 or subtask > SUBTASKS:
        raise Exception("Invalid subtask number.")

    defaults = (1000, [0,2,5,6,10,11], list(range(len(tg.ID_TYPES))))

    MAX_N, allowed_trees, allowed_ids = (
        (), # 1-based subtasks,
        (200, defaults[1], defaults[2]),
        (defaults[0], [0], defaults[2]),
        (defaults[0], defaults[1], [2]),
        defaults
    )[subtask]

    # if constraints are not specified, will generate them randomly
    if len(sys.argv) < ARGS:
        N = random.randint(2, MAX_N)
        tree_type = random.choice(allowed_trees)
        id_type = random.choice(allowed_ids)

    # checks if valid
    if N < 1 or N > MAX_N:
        raise Exception("N out of bounds for subtask.")

    if tree_type not in allowed_trees:
        raise Exception("Invalid tree type for subtask.")

    if id_type not in allowed_ids:
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

    print(grader_type,N,subtask)
    print(*parent)
