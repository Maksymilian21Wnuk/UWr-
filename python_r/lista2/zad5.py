

def kompresja(tekst):
    ile = 1
    res = []
    for start in range(len(tekst) - 1):
        c1 = tekst[start]
        c2 = tekst[start + 1]
        if (c1 == c2):
            ile += 1
        else:
            res.append((c1, ile))
            ile = 1
    if c1 == c2:
        res.append((c1, ile))
    else:
        res.append((c2, 1))
    
    return res
    
    
    
def dekompresja(tekst):
    res = ""
    for krotka in tekst:
        res += krotka[0] * krotka[1]
    return res


def main():
    # testy
    LOREM = False
    
    TXTs = ["suuuuper", "hhaahhhhee" , "abccdd", "esss", "SSSSSSSS", "sssdddd", "XXXd"]
    for txt in TXTs:            
        txt_compressed = kompresja(txt)
        print(txt_compressed)
        print(dekompresja(txt_compressed))
        # assert that decompression of compressed text is
        # same as input text
        assert dekompresja(txt_compressed) == txt

        
    if (LOREM):
        print("\n lorem test: \n")
        with open("lorem.txt") as txt:
            txt = kompresja(txt.read())
            print(txt)
            print(dekompresja(txt))

if __name__ == "__main__":
    main()