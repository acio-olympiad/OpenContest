import os

ALLOWED_TREES = [0,2,5,6,10,11]

typename = {
    0: "line",
    2: "random",
    5: "tri",
    6: "balanced",
    10: "half-fishbone",
    11: "spikey",
}

def print_system(command):
    print("Generating", command.split()[-1])
    os.system(command)

def gen_specific(of, sb, N, tt, it):
    print_system("python panther-gen.py %d %d %d %d > %s-sub%d.in" % (sb, N, tt, it, of, sb))

def gen_random(of, sb):
    print_system("python panther-gen.py %d > %s-sub%d.in" % (sb,of,sb))

def sub1():
    print("Subtask 1...")
    gen_specific("min", 1, 1, 0, 0)
    gen_specific("size2", 1, 2, 0, 0)
    gen_specific("size10", 1, 10, 2, 0)
    gen_specific("size199", 1, 199, 2, 0)
    gen_specific("size127-balanced", 1, 127, 6, 0)
    gen_specific("size128-balanced", 1, 128, 6, 0)

    gen_specific("random-ids", 1, 200, 2, 0)
    gen_specific("ascending-ids", 1, 200, 2, 1)
    gen_specific("descending-ids", 1, 200, 2, 2)

    for tt in ALLOWED_TREES:
        gen_specific("max-%s" % typename[tt], 1, 200, tt, 0)

    for i in range(5):
        gen_random("random%d" % i, 1)

def sub2():
    print("\nSubtask 2...")
    gen_specific("min", 2, 1, 0, 0)
    gen_specific("size2", 2, 2, 0, 0)
    gen_specific("size10", 2, 10, 0, 0)
    gen_specific("size512", 2, 512, 0, 0)
    gen_specific("size999", 2, 999, 0, 0)
    gen_specific("max", 2, 1000, 0, 0)

    gen_specific("random-ids", 2, 1000, 0, 0)
    gen_specific("ascending-ids", 2, 1000, 0, 1)
    gen_specific("descending-ids", 2, 1000, 0, 2)

    for i in range(3):
        gen_random("random%d" % i, 2)

def sub3():
    print("\nSubtask 3...")
    gen_specific("min", 3, 1, 0, 2)
    gen_specific("size2", 3, 2, 0, 2)
    gen_specific("small", 3, 10, 2, 2)
    gen_specific("medium", 3, 100, 2, 2)
    gen_specific("size512", 3, 512, 2, 2)
    gen_specific("size511-balanced", 3, 511, 6, 2)
    gen_specific("size512-balanced", 3, 512, 6, 2)
    gen_specific("size999", 3, 999, 2, 2)

    for tt in ALLOWED_TREES:
        gen_specific("max-%s" % typename[tt], 3, 1000, tt, 2)

    for i in range(5):
        gen_random("random%d" % i, 3)

def sub4():
    print("\nSubtask 4...")
    gen_specific("min", 4, 1, 0, 0)
    gen_specific("size2", 4, 2, 0, 0)
    gen_specific("size3", 4, 3, 2, 0)
    gen_specific("size10", 4, 10, 2, 0)
    gen_specific("size100", 4, 100, 2, 0)
    gen_specific("size512", 4, 512, 2, 0)
    gen_specific("size511-balanced", 4, 511, 6, 0)
    gen_specific("size512-balanced", 4, 512, 6, 0)
    gen_specific("size999", 4, 999, 2, 0)

    gen_specific("random-ids", 4, 1000, 2, 0)
    gen_specific("ascending-ids", 4, 1000, 2, 1)
    gen_specific("descending-ids", 4, 1000, 2, 2)

    for tt in ALLOWED_TREES:
        gen_specific("max-%s" % typename[tt], 4, 1000, tt, 0)

    for i in range(5):
        gen_random("random%d" % i, 4)

sub1()
sub2()
sub3()
sub4()