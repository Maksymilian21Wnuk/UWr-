from collections import deque


OPERATORS = {'+' : lambda x,y : x + y, '-' : lambda x,y : x - y, '/' : lambda x,y : x / y, '*' : lambda x,y : x * y}

OP_PRIO = {'(' : 0, '+' : 1, '-' : 1, '*' : 2, '/' : 2 }

def solve_onp(q):
    q_temp =([])
    res = 0
    while(len(q) > 0):
        val = q.popleft()
        print(q_temp, res)
        if val in list(OPERATORS.keys()):
            foo = OPERATORS[val]
            a1 = q_temp.pop()
            a2 = q_temp.pop()
            temp = foo(a2, a1)
            q_temp.append(temp)
            res = temp
        elif val.isnumeric():
            q_temp.append(int(val))
    
    print(res)

def make_onp(q):
    while (len(q) > 0):
        val = q.popleft()
    


def main():
    q1 = deque(['2', '3', '4', '+', '-'])
    q2 = deque(['2', '7', '+', '3', '/', '14', '3', '-', '4', '*', '+', '2', '/'])
    solve_onp(q1)
    solve_onp(q2)



if __name__ == "__main__":
    main()