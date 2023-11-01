import numpy as np
import random

# teksty w plikach t.txt oraz lorem.txt

def skroc(tekst, ile):
    # moze sie kwadracić
    bool_table = np.full(len(tekst), True)
    random_ints = random.sample(range(len(tekst)), ile)
    
    bool_table[random_ints] = False
    
    return tekst[bool_table]

def uprosc_zdanie(tekst, dl_slowa, liczba_slow):
    tekst = np.array([x for x in tekst.split() if len(x) < dl_slowa])

    if (liczba_slow < len(tekst)):
        tekst = skroc(tekst, len(tekst) - liczba_slow)
    
    tekst = ' '.join(tekst)

    print(tekst)
    

def main():
    print("krotkie zdanie z wikipedii: \n")
    with open("t.txt") as file:
        uprosc_zdanie(file.read(), 6, 4)
        
    print("\ntekst z przykladu z listy: \n")    
    tekst = "Podział peryklinalny inicjałów wrzecionowatych \
        kambium charakteryzuje się ścianą podziałową inicjowaną \
        w płaszczyźnie maksymalnej."
    uprosc_zdanie(tekst, 10, 5)
    
    print("\nDluzsze lorem ipsum: \n")
    with open("lorem.txt") as file:
        uprosc_zdanie(file.read(), 4, 100)
    
    
main()