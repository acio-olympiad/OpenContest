import sys
N = int(sys.argv[1])
print(2, N, 4)
s2 = ["-1"]
for i in range(1, N):
    s2.append(str(((i-1)//2) * 2))

print(" ".join(s2))
