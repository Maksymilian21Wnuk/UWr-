import time
import numpy as np
import pandas as pd
from math import sqrt

# w ponizszym rozwiazaniu zadania nie korzystalem
# z modulu timeit, uznałem że moduł time jest lepszy do
# tworzenia pomiarów w programie

def pierwsze_imperatywna(n):
    res = []
    prime = True
    for i in range(2, n):
        for divisor in range(2, int(sqrt(n)) + 1):
            if i % divisor == 0:
                prime = False
                break            
        if (prime):
            res.append(i)
        prime = True
    return res

def pierwsze_skladana(n):
    return [x for x in range(2, n) 
            if all(x % i != 0 
                   for i in range(2, int(sqrt(n)) + 1))]
    
def pierwsze_funkcyjna(n):
    return list(filter(lambda x : all(x % i != 0 
                                      for i 
                                      in range(2, int(sqrt(n)) + 1)),
                                      range(2, n))) 


def main():
    # format lepszy
    np.set_printoptions(suppress=True)
    f = [pierwsze_imperatywna, pierwsze_funkcyjna, pierwsze_skladana]
    res_array = np.zeros((11, 4), dtype=float)

    j = 0
    for i in range(10_000, 11_000_0 + 1, 10_000):
        res_array[j][0] = i
        j += 1

    for k in range(1, 4):

        j = 0
        for i in range(10_000, 11_000_0 + 1, 10_000):
            start = time.time()
            f[k - 1](i)
            end = time.time()
            res_array[j][k] = end - start 
            j += 1


    df = pd.DataFrame(res_array, columns=["n", "imperatywna","funkcyjna" ,"skladana"])
    df["n"] = df["n"].astype(int)
    print(df)
    
if __name__ == "__main__":
    main()
    

