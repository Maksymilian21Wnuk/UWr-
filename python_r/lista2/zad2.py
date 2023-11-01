import time
import functools
import sys

### dla sudan_cache(1,22,22) bardzo szybko ~1.8596649169921875e-05
### bez cache okolo 0.91 sekundy
### dla sudan_cache(1, 25, 25) czas 3.743171691894531e-05
### bez cache 6.93 sekund

@functools.cache
def sudan_cache(n, x, y):
  if n == 0:
    return x + y
  elif y == 0:
    return x
  else:
    return sudan_cache(n - 1, sudan_cache(n, x, y - 1), sudan_cache(n, x, y - 1) + y)
    

def sudan(n, x, y):
  if n == 0:
    return x + y
  elif y == 0:
    return x
  else:
    return sudan(n - 1, sudan(n, x, y - 1), sudan(n, x, y - 1) + y)


def main():
  sys.setrecursionlimit(1500)
  start = time.time()
  sudan(1,25,25)
  #sudan(1,22,22)
  print("Czas bez cache z functools: {}", time.time() - start)
  
  start = time.time()
  sudan_cache(1, 25, 25)
  print("Czas z cache functools: {}", time.time() - start)




if __name__ == "__main__":
    main()