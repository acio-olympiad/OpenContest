import os
import sys

def grid(x,y,of):
    print("Generating", of)
    with open(of, "w") as f:
        f.write("%d %d\n" % (100000, x*y))
        assert(x*y <= 100000)
        for i in range(1,x+1):
            for j in range(1,y+1):
                f.write("%d %d\n" % (i, j))

for root, dirs, files in os.walk("gen_specs"):
    for fn in files:
        cmd = "./generator < " + os.path.join(root, fn) + " > " + "gen_" + fn
        print(cmd)
        os.system(cmd)

grid(1, 100000, "grid1.in")
grid(3, 33333, "grid2.in")
