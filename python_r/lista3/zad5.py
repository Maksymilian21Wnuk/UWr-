

def max_sublist_sum(l):
    n = len(l)
    res = -1 * float('inf')
    indeces = [-1, -1]
    
    for i in range(n):
        cur_sum = 0
        for j in range(i, n):
            cur_sum = sum(l[i:j+1])
            if (cur_sum > res):
                res = cur_sum
                indeces = [i, j + 1]
    
    return res

def main():
    print(max_sublist_sum([3, -10, 20, -20, 2, 4, 5, 6, 7, 8, 9]))
    print(max_sublist_sum([-1, -100, -23]))
    print(max_sublist_sum([-5, 10, 5, -30, 400]))
    print(max_sublist_sum([10, -50, 1000, -10000, -500, 20, 30]))
    print(max_sublist_sum([10, 3, -50, 13, -50, -100, 150, 13]))

if __name__ == "__main__":
    main()