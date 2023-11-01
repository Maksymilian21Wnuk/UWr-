


# w zadaniu omijam spacje za pomocą replace !

# funkcja do wypisania wyniku w postaci string  
def print_res(res, txt):
    txt = txt.replace(' ', '')
    i = 1
    for elem in res:
        print("wynik nr {}: {}".format(i, txt[elem[0]:elem[0] + elem[1]]))
        i += 1
        
def find_palindroms(text):
    text = text.replace(" ", '')
    print(text)
    n = len(text)
    dp = [[0] * n for i in range(n)]
    res = []
    maximum = 0
 
    for k in range(n):
        for i in range(n - k):
            j = i + k
            if k == 0:
                dp[i][j] = 1
            elif k == 1:
                dp[i][j] = (text[i] == text[j])
            else:
                dp[i][j] = ((text[i] == text[j]) and dp[i + 1][j - 1])
 
            if dp[i][j]:
                temp = text[i:j+1]
                if ( len(temp) > 1):
                    res.append((i, len(temp)))
                    if (maximum < len(temp)):
                        maximum = len(temp)

    return list(filter(lambda x : x[1] == maximum, res))

def main():
    print(find_palindroms("asd ddss asddffs sddfe aabbaa"))
    print(find_palindroms("aabsdfabcddcba"))
    print(find_palindroms("ab  ba"))
    
    print_res(find_palindroms("ab b a"), "ab  ba")
    print_res(find_palindroms("asd dsa asddffs sddfe aabbaa"), "asd dsa asddffs sddfe aabbaa")
    
    # przypadek dla np. trzech palindromow w tekscie
    print(find_palindroms("ab b a   cdda"))
    print_res(find_palindroms("ab b a   cdd c   rrrr"), "ab b a   cdd c   rrrr")




if __name__ == "__main__":
    main()