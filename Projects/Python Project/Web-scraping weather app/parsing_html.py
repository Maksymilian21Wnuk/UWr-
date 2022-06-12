import requests
import re
import os.path
from datetime import date, datetime
from bs4 import BeautifulSoup


class Weather():
    def __init__(self):
        self.url = "https://pogoda.wp.pl/"        
        self.city_dict = {}
        self.current_time = None
        self.current_date = None
        self.soup = None

    def __getitem__(self, city_name):
        return self.city_dict[city_name]
        
    def run(self):
        page = requests.get(self.url)
        self.soup = BeautifulSoup(requests.get(self.url).content, "html.parser")

        self.current_time = datetime.now().strftime("%H:%M:%S")
        self.current_date = date.today()

        res = self.soup.find(id="__layout")
        weather_elems = res.find_all('li', class_='el temp')
        for elem in weather_elems:
            city = elem.find("a")
            degrees = re.search("data-temp=""(.*)"" d", str(city)).group(1)
            city = city.text
            if city == "Adamenzork" :
                break
            degrees = int(degrees[1:-1])
            self.city_dict[city] = degrees
        
    def city_weather(self):
        try:
            for item in self.city_dict.items():
                print("{} : {}".format(item[0], item[1]))
        except:
            print("Error: no parsing was done")

    def to_file(self):
        path_name = 'weather_file.txt'
        if os.path.exists(path_name):
            def write_to_file():
                file = open(path_name, 'a')
                file.write("Date: {} {}\n".format(self.current_time, self.current_date))
                file.write("Average temperature: {}\n".format(str(self.average())))
                for item in self.city_dict.items():
                    file.write("{} : {}\n".format(item[0], item[1]))
                file.write("\n")
                file.close()
                
            write_to_file()
            
        else:
            file = open(path_name, 'w')
            file.write('Weather data \n')
            write_to_file()   

    def average(self):
        temp = 0
        for val in self.city_dict.values():
            temp += val
        return round(temp / len(self.city_dict), 2)
