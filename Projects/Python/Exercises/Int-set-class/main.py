from int_sets import *


def main():

    n1 = Number(1)
    n2 = Number(5)
    n3 = Number(6)
    v1 = Variable("28y")
    v2 = Variable("100x")
    v3 = Variable("3z")
    IntSet.append_eval("z", 10)
    IntSet.append_eval("a", 30)
    
    my_set = IntSet([n1, n2, n3, v1, v2, v3])
    print(my_set)
    print(my_set.evaluate())
    IntSet.append_eval("x", 10)
    print(my_set.evaluate())

if __name__ == "__main__":
    main()
