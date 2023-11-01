import math
import random 

# sluzy do wypisywania aktualnej wartosci wyniku,
# wypisuje duzo wartosci dlatego default false
WYPISZ_AKTUALNE = False

def start(n):
    ltwo = 0
    
    for cltwt in range(1, n + 1):
        # losuję wspolrzedne z przedzialu [0,1]
        x = random.random()
        y = random.random()
        # sprawdzam czy trafił w okręg wpisany
        # w kwadrat o boku 1
        if (((x - 0.5) ** 2 + (y - 0.5) ** 2) <= 0.5**2):
            ltwo += 1
        
        res = (4 * ltwo) / cltwt

        if WYPISZ_AKTUALNE : print(res)
        
    return res


def main():
    for i in range(25, 10000, 500):
        print(i, ":", start(i))



if __name__ == "__main__":
    main()