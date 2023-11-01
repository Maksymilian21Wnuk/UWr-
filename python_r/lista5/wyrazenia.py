

class Wyrazenie:
    
    def oblicz(self):
        pass
    
    def __str__(self) -> str:
        pass
    
    def __add__(self, right):
        return Dodaj(self, right)
    
    def __mul__(self, right):
        return Razy(self, right)
    
    def pochodna(self, zmienna):
        pass
    
    
    
class VariableNotFoundException(Exception):
    def __init__(self, nazwa) -> None:
        self.nazwa = nazwa
        super().__init__(f"Brak wartości zmiennej {nazwa}")


class Zmienna(Wyrazenie):
    def __init__(self, nazwa):
        self.nazwa = nazwa
    
    def oblicz(self, zmienne):
        if self.nazwa in zmienne:
            return zmienne[self.nazwa]
        else:
            raise VariableNotFoundException(self.nazwa)
        
    def __str__(self) -> str:
        return self.nazwa
    
    def pochodna(self, zmienna):
        if self.nazwa == zmienna:
            return Stala(1)
        else:
            return Stala(0)
        
        
class Stala(Wyrazenie):
    def __init__(self, wartosc) -> None:
        self.wartosc = wartosc
    
    def oblicz(self, zmienne):
        return self.wartosc

    def __str__(self) -> str:
        return str(self.wartosc)
    
    def pochodna(self, zmienna):
        return Stala(0)
    
class Dodaj(Wyrazenie):
    def __init__(self, lewy, prawy) -> None:
        self.lewy = lewy
        self.prawy = prawy
    
    def oblicz(self, zmienne):
        return self.lewy.oblicz(zmienne) + self.prawy.oblicz(zmienne)
    
    def __str__(self):
        return f"({self.lewy} + {self.prawy})"
    
    def pochodna(self, zmienna):
        return Dodaj(self.lewy.pochodna(zmienna), self.prawy.pochodna(zmienna))
    

class Razy(Wyrazenie):
    def __init__(self, lewy, prawy) -> None:
        self.lewy = lewy
        self.prawy = prawy
    
    def oblicz(self, zmienne):
        return self.lewy.oblicz(zmienne) * self.prawy.oblicz(zmienne)
    
    def __str__(self):
        return f"({self.lewy} * {self.prawy})"
    
    def pochodna(self, zmienna):
        return Dodaj(Razy(self.lewy.pochodna(zmienna), self.prawy), Razy(self.lewy, self.prawy.pochodna(zmienna)))