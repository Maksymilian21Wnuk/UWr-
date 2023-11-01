# znaki do usuniecia z tekstu
chars_to_remove = [" ", ",", "?", "\n", "!", ":", "."]


def is_palindrom(text):
    text = text.lower()

    # usuwa znaki przesiadkowe spacje ? ! itp.
    for char in chars_to_remove:
        text = text.replace(char, '')

    # sprawdz czy taki sam od tyłu tekst
    return text == text[::-1]


def test(text):
    print(text, ":" ,is_palindrom(text))

def main():
    # teksty do testowania
    texts = ["ók ó.....", 
             "oko", 
             "Míč omočím.", 
             "Eine güldne, gute Tugend: Lüge nie!", 
             "a   a ??  a ???",
             "Kobyła ma mały bok.",
             "kob",
             "basdfwerqweasf"]
    for t in texts:
        test(t)




if __name__ == "__main__":
    main()