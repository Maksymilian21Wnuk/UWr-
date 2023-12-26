'''
Program for concurrently
checking the changes in given 
websites with given delay time
'''


import requests
import time
import difflib
import threading


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


def test(url, delay):
    prev_txt = open_url(url).text
    while(1):
        time.sleep(delay)
        txt = open_url(url).text
        
        print(f"Url : {url}")
        difs = difflib.unified_diff(prev_txt.splitlines(), txt.splitlines(), lineterm='')
        
        # make list out of generator
        difs = list(difs)
        
        if len(difs) == 0:
            print("No change in website\n")
        else:   
            for d in difs:
                print(d)
        # update compared pages 
        prev_txt = txt
        
# url that never changes
NO_CHANGE_URL = "https://man7.org/linux/man-pages/man2/fork.2.html"
# url that shows time, changes every one second
# easily can see differences between pages
CLOCK_URL = "https://dayspedia.com/time/online/"
# some weather website
WEATHER = "https://pogoda.interia.pl/"



def main():
    # urls dicts with seconds for delay
    urls = {NO_CHANGE_URL : 3, CLOCK_URL : 1, WEATHER : 5} 
    
    for i in range(6):
        for item in urls.items():
            threading.Thread(target = test, args = (item[0], item[1],)).start()
    # since program works in real time,
    # no need to thread join
    
    
if __name__ == "__main__":
    main()