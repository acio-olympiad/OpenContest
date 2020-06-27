import sys

cnt = 1

def pure(x,sb):
    global cnt
    with open("gen_specs/%d-%d-pure-auto.in" % (sb, cnt), "w") as f:
        f.write("%d %d\n" % (1, sb))
        X = [200, 2000, 100000, 100000, 1000000]
        f.write("%d %d\n" % (x, X[sb-1]))
    cnt += 1

def mixed(types,sb):
    global cnt
    with open("gen_specs/%d-%d-mixed-auto.in" % (sb, cnt), "w") as f:
        X = [200, 2000, 100000, 100000, 1000000]
        t = len(types)
        f.write("%d %d\n" % (t, sb))
        for i in types:
            f.write("%d %d\n" % (i, X[sb-1]//t))
    cnt += 1

Sub1Mixed = [1,2,3]
Sub2Mixed = [1,2,3,4]
Sub3Mixed = [-1] #NA
Sub4Mixed = [1,2,3,4,5]
Sub5Mixed = [1,2,3,4,5,6]
def subtask1():
    print("Made", 30, "cases")
    for i in range(6):
        pure(1,1)
    for i in range(10):
        pure(2,1)
        pure(3,1)
    for i in range(4):
        mixed(Sub1Mixed, 1)
        
def subtask2():
    print("Made", 30, "cases")
    for i in range(2):
        pure(1,2)
    for i in range(6):
        pure(2,2)
        pure(3,2)
        pure(4,2)
        pure(5,2)
    for i in range(4):
        mixed(Sub2Mixed,2)
        
def subtask3():
    print("Made", 15, "cases")
    for i in range(5):
        pure(4,3)
        pure(5,3)
        pure(6,3)
        
def subtask4():
    print("Made", 10, "cases")
    pure(1,4)
    for i in range(3):
        pure(2,4)
        pure(3,4)
    for i in range(3):
        mixed(Sub4Mixed,4)
def subtask5():
    print("Made", 5, "cases")
    pure(2,5)
    pure(3,5)
    pure(6,5)
    mixed(Sub5Mixed,5)
    mixed(Sub5Mixed,5)
        
subtask1()
subtask2()
subtask3()
subtask4()
subtask5()
