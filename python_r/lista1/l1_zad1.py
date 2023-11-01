import numpy as np
from decimal import *

VAT = 0.23

# vat mnozony przez sume listy
def vat_faktura(lista):
    return lista.sum() * VAT
    
# kazdy element listy mnozony i potem sumowany
def vat_paragon(lista):
    return (lista * VAT).sum()

# pomocnicza funkcja do testowania wartości kolejno
# faktury paragonu oraz czy wartości są takie same
def test(lista):
    print("f: ", vat_faktura(lista), "p:", vat_paragon(lista), vat_faktura(lista) == vat_paragon(lista))

def main():
    lista1 = np.array([5.3, 23.1, 90.5, 100.0, 4.02], dtype=float)
    lista2 = np.arange(15, dtype=int)
    lista3 = np.array([1, 23, 100, 20], dtype = float)

    test(lista1)
    test(lista2)
    test(lista3)    
    
    # test lista1 zamienionej na typ Decimal zamiast float
    ldecim = np.array([Decimal(str(x)) for x in lista1])
    print("Dla decimal1: ", ldecim.sum() * Decimal(str(VAT)) == (ldecim * Decimal(str(VAT))).sum())
    
    ldecim2 = np.array([Decimal(str(x)) for x in lista2])
    print("Dla decimal2: ", ldecim2.sum() * Decimal(str(VAT)) == (ldecim2 * Decimal(str(VAT))).sum())
    
    # wypisuje już true, zamiast false


if __name__ == "__main__":
    main()