import sys
import random

N = int(sys.argv[1])
mid = int(sys.argv[2])
print(2, N, 4)
s2 = ["-1"]
ch = [0]

for i in range(1, mid):
    assert(ch[(i-1)//2] < 2)
    s2.append(str((i-1)//2))
    ch[(i-1)//2] += 1
    ch.append(0)

for i in range(mid, N):
    assert(ch[((i-1)//2)*2] < 2)
    s2.append(str(((i-1)//2)*2))
    ch[((i-1)//2)*2] += 1
    ch.append(0)

'''
for i in range(500, N):
    choice = random.randint(max(0, i-5), i-1)
    while ch[choice] >= 2:
        choice = random.randint(max(0, i-5), i-1)
    ch[choice] += 1
    s2.append(str(choice))
    ch.append(0)
'''

print(" ".join(s2))
