import os

def print_system(command):
    print(command)
    os.system(command)

def gen_specific(of, sb, N, M, tt):
    print_system("python3 gen/vibe-gen.py %d %d %d %d > %s" % (sb, N, M, tt, of))

def gen_random(of, sb):
    print_system("python3 gen/vibe-gen.py %d > %s" % (sb,of))

def sub1():
    print("Subtask 1...")
    gen_specific("minN-sub1.in", 1, 2, 100000, 0)
    gen_specific("minM-sub1.in", 1, 100, 1, 9)
    gen_specific("small-sub1.in", 1, 100, 100, 9)

    for tt in range(13):
        gen_specific("type%d-sub1.in" % tt, 1, 100, 100000, tt)

    for i in range(5):
        gen_random("random-sub1-%d.in" % i, 1)

def sub2():
    print("Subtask 2...")
    gen_specific("minN-sub2.in", 2, 2, 100000, 0)
    gen_specific("minM-sub2.in", 2, 1000, 1, 9)
    gen_specific("small-sub2.in", 2, 1000, 1000, 9)
    
    for tt in range(13):
        gen_specific("type%d-sub2.in" % tt, 2, 1000, 100000, tt)

    for i in range(5):
        gen_random("random-sub2-%d.in" % i, 2)

def sub3():
    print("Subtask 3...")
    gen_specific("minN-sub3.in", 3, 2, 1, 0)
    gen_specific("small-sub3.in", 3, 10, 1, 0)
    gen_specific("max-sub3.in", 3, 100000, 1, 0)

    for i in range(5):
        gen_random("random-sub3-%d.in" % i, 3)

    for i in range(5):
        gen_specific("max-random-sub3-%d.in" % i, 3, 100000, 1, 0)


def sub4():
    print("Subtask 4...")
    gen_specific("minN-sub4.in", 4, 2, 1, 0)
    gen_specific("small-sub4.in", 4, 10, 1, 9)
    
    for tt in range(13):
        gen_specific("type%d-sub4.in" % tt, 4, 100000, 1, tt)

    for i in range(10):
        gen_random("random-sub4-%d.in" % i, 4)

def sub5():
    print("Subtask 5...")
    gen_specific("minN-sub5.in", 5, 2, 100000, 0)
    gen_specific("minM-sub5.in", 5, 100000, 1, 0)
    gen_specific("small-sub5.in", 5, 1000, 1000, 0)
    gen_specific("max-sub5.in", 5, 100000, 100000, 0)

    for i in range(5):
        gen_random("random-sub5-%d.in" % i, 5)

def sub6():
    print("Subtask 6...")
    gen_specific("minN-sub6.in", 6, 2, 100000, 0)
    gen_specific("minM-sub6.in", 6, 100000, 1, 9)
    gen_specific("small-sub6.in", 6, 10, 10, 9)
    gen_specific("max-sub6.in", 6, 100000, 100000, 9)
    
    for tt in range(13):
        gen_specific("type%d-sub6.in" % tt, 6, 100000, 100000, tt)

    for i in range(5):
        gen_random("random-sub6-%d.in" % i, 6)


sub1()
sub2()
sub3()
sub4()
sub5()
sub6()
