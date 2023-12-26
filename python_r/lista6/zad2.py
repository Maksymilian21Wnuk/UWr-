import requests
import time
import difflib


def open_url(url):
    try:
        tekst = requests.get(url)
        tekst.raise_for_status()
        return tekst
    except requests.exceptions.HTTPError as errh:
        print("Http Error:", errh)
    except requests.exceptions.ConnectionError as errc:
        print("Error Connecting:",errc)
    except requests.exceptions.Timeout as errt:
        print("Timeout Error:",errt)


def test(urls):
    prev_txt = [open_url(url).text for url in urls]
    while(1):
        time.sleep(TIME)
        txt = [open_url(url).text for url in urls]
        
        for idx in range(len(prev_txt)):
            print(f"Url : {urls[idx]}")
            difs = difflib.unified_diff(prev_txt[idx].splitlines(), txt[idx].splitlines(), lineterm='')
            
            # make list out of generator
            difs = list(difs)
            
            if len(difs) == 0:
                print("No change in website\n")
            else:   
                for d in difs:
                    print(d)
            # update compared pages 
            prev_txt[idx] = txt[idx]
        
# url that never changes
NO_CHANGE_URL = "https://man7.org/linux/man-pages/man2/fork.2.html"
# url that shows time, changes every one second
# easily can see differences between pages
CLOCK_URL = "https://dayspedia.com/time/online/"
TIME = 1


def main():
    #test(NO_CHANGE_URL)
    test([CLOCK_URL, NO_CHANGE_URL])
        

if __name__ == "__main__":
    main()