from wyrazenia import *


def main():
    #1 test wyrazenia jakiegos prostego
    wyr1 = Dodaj(Zmienna("y"), Razy(Zmienna("x"), Stala(30)))
    print(wyr1)
    
    #2 test exception wlasnego zwiazanego z brakiem zmiennej
    try:
        wyr1.oblicz({"y":3, "x":2})
    except VariableNotFoundException:
        print("not defined")
    else:
        print(wyr1.oblicz({"y":3, "x":2}))
    
    try:
        wyr1.oblicz({"t" : 30})
    except VariableNotFoundException:
        print("not found variable exception")
    else:
        print(wyr1.oblicz({"t" : 30}))
    
    #3 test pochodnych i wyliczania wartosci w punkcie    
    wyr2 = Dodaj(Zmienna("x"), Razy(Zmienna("x"), Zmienna("x")))
    print(f"\nFunkcja: {wyr2}")
    print(f"Pochodna: {wyr2.pochodna('x')} \nJej wartość w x=10 : {wyr2.pochodna('x').oblicz({'x' : 10})}\n")
        
    #4 test operatora dodawania i mnozenia
    wyr3a = Zmienna("x")
    wyr3b = Razy(Zmienna("x"), Stala(42))
    wyr3c = wyr3a + wyr3b
    wyr3d = wyr3a * wyr3b
    print(wyr3c)
    print(wyr3d * wyr3c)
    

if __name__ == "__main__":
    main()