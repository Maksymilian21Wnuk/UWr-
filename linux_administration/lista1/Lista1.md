# Lista 2

### Zadanie 1
Stare wersje kernela:
https://cdn.kernel.org/pub/linux/kernel/
Link do dysu ze starymi jądrami
https://drive.google.com/drive/folders/1LcBZQtI0uFmEAW_J40ZgxQWTKUiTnwlj?usp=sharing
```shell=
DATA=cloc_output.txt

if [ -f "$DATA" ]; then
    echo "Deleting $DATA."
    rm $DATA
fi

YEAR=1993

for ARCHIVE in ./archives/*
do
    printf "\nLinux kernel in $YEAR" | tee -a $DATA
    YEAR=$(($YEAR+2))
    cloc -md $ARCHIVE >> $DATA 
done
```

Do plotowania danych
```python 
import json
import matplotlib.pyplot as plt

file = open("cloc_output.json")
data = json.load(file)

years = [ i["year"] for i in data["data"]]
fig1, axs = plt.subplots(3)

print("Code")
y = [d["SUM"]["code"] for d in data["data"]]
axs[0].plot(years, y)
axs[0].set_title("Lines of code")
for d in data["data"]:
    print("{} {}".format(d["year"], d["SUM"]["code"]))

print("Files")
y = [d["SUM"]["nFiles"] for d in data["data"]]
axs[1].plot(years, y)
axs[1].set_title("Number of files")
for d in data["data"]:
    print("{} {}".format(d["year"], d["SUM"]["nFiles"]))


# W stanach programista zarabia srednio 100k$ na rok
# Średio deweloper pisze 80 linii kodu dziennie - 240 * 80 = 19 200 linii kodu rocznie
print("Personyears")
y = [(d["SUM"]["code"] / 19200) for d in data["data"]]
axs[2].plot(years, y)
axs[2].set_title("Personyears")
for d in data["data"]:
    workyears = (d["SUM"]["code"] / 19200)
    print("{} {:8.2f} - {:8.2f}k$".format(d["year"], workyears, workyears * 100))

languages = list(filter( lambda x : x not in ["year", "header", "SUM"],
                data['data'][-1].keys()))
language_data = {l : [] for l in languages}


for l in languages:
    for d in data['data']:
        if l in d:
            language_data[l].append(d[l]['code'])
        else:
            language_data[l].append(0)

fig2, ax = plt.subplots()
for l in languages:
    ax.plot(years, language_data[l], label=l)

ax.legend(loc = 'upper left')
plt.show()

file.close()
```

Linux kernel in 1993
cloc|github.com/AlDanial/cloc v 1.86  T=0.71 s (759.5 files/s, 243596.8 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|282|17068|20636|103673
C/C++ Header|205|3440|5403|14957
Assembly|19|831|1197|3388
make|28|329|316|1022
Bourne Shell|3|22|139|132
IDL|1|0|0|8
--------|--------|--------|--------|--------
SUM:|538|21690|27691|123180

Linux kernel in 1995
cloc|github.com/AlDanial/cloc v 1.86  T=1.25 s (688.0 files/s, 239932.8 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|400|29756|39533|165407
C/C++ Header|365|6830|10819|29610
Assembly|38|1645|2873|8120
make|47|599|543|1715
Perl|1|95|118|714
Pascal|1|0|0|133
Smalltalk|1|29|0|130
Bourne Shell|3|26|70|114
IDL|1|0|0|8
--------|--------|--------|--------|--------
SUM:|857|38980|53956|205951

Linux kernel in 1997
cloc|github.com/AlDanial/cloc v 1.86  T=3.06 s (596.2 files/s, 238087.2 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|778|70273|90160|402561
C/C++ Header|821|15396|24576|71077
Assembly|110|4591|11859|25247
make|93|942|958|3178
TeX|3|307|11|2116
Bourne Shell|7|246|422|1193
Perl|1|97|118|728
Tcl/Tk|2|61|48|409
Smalltalk|1|49|0|269
C++|1|38|33|254
Pascal|1|0|0|137
awk|1|7|13|134
XML|1|12|0|50
IDL|1|0|0|8
Markdown|1|1|0|3
--------|--------|--------|--------|--------
SUM:|1822|92020|128198|507364

Linux kernel in 1999
cloc|github.com/AlDanial/cloc v 1.86  T=7.15 s (586.4 files/s, 237293.0 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|1891|168482|205289|936929
C/C++ Header|1864|37720|54343|199953
Assembly|226|7243|17740|47220
make|178|2034|1765|8187
TeX|3|432|15|3087
Bourne Shell|11|218|823|1734
Perl|4|115|137|860
Tcl/Tk|2|61|65|410
HTML|1|1|0|353
Smalltalk|1|63|0|338
Scheme|1|63|0|218
awk|3|22|10|133
Pascal|1|15|0|102
sed|1|0|0|72
Bourne Again Shell|3|3|11|24
IDL|1|0|0|8
Markdown|1|1|0|3
--------|--------|--------|--------|--------
SUM:|4192|216473|280198|1199631

Linux kernel in 2001
cloc|github.com/AlDanial/cloc v 1.86  T=13.64 s (546.5 files/s, 233279.5 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|3237|316535|371258|1677985
C/C++ Header|3459|82557|120029|409896
Assembly|399|22047|44871|111554
make|305|2855|2784|7444
Bourne Shell|20|351|1134|2856
Perl|9|397|609|1983
TeX|2|175|3|1200
Tcl/Tk|2|81|67|577
HTML|1|0|0|374
Smalltalk|1|65|0|348
awk|5|39|21|249
Scheme|1|63|0|218
Pascal|1|12|0|83
sed|1|0|0|72
C++|2|21|48|62
Bourne Again Shell|5|10|28|49
Prolog|1|3|0|30
IDL|1|0|0|8
--------|--------|--------|--------|--------
SUM:|7452|425211|540852|2214988

Linux kernel in 2003
cloc|github.com/AlDanial/cloc v 1.86  T=24.10 s (566.1 files/s, 228292.7 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|6168|557161|658343|2903663
C/C++ Header|6102|141339|220683|744466
Assembly|651|29365|61966|151022
make|649|3285|4266|9691
yacc|4|394|270|2601
Perl|12|404|478|2478
Bourne Shell|34|250|931|2102
C++|5|185|145|1248
lex|4|166|191|1168
TeX|1|108|3|918
HTML|2|58|0|750
Glade|1|53|0|490
NAnt script|1|86|0|303
Bourne Again Shell|5|36|45|235
Scheme|1|63|0|218
Objective C++|1|55|0|189
ASP|1|33|0|136
Pascal|1|13|3|84
awk|1|10|3|60
Prolog|1|3|0|30
--------|--------|--------|--------|--------
SUM:|13645|733067|947327|3821852

Linux kernel in 2005
cloc|github.com/AlDanial/cloc v 1.86  T=27.81 s (559.6 files/s, 219764.2 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|7093|635120|730913|3311272
C/C++ Header|6837|144852|224844|761082
Assembly|788|31946|69277|164838
make|742|3717|4672|11064
Perl|18|541|678|3400
yacc|4|395|270|2603
Bourne Shell|39|299|929|1789
C++|5|200|156|1311
lex|4|166|194|1176
TeX|1|108|3|911
HTML|2|58|0|750
Glade|1|53|0|492
NAnt script|1|80|0|250
Scheme|1|63|0|218
Objective C++|1|55|0|189
TNSDL|1|38|0|162
ASP|1|33|0|136
awk|2|14|7|101
Bourne Again Shell|3|8|29|52
Clojure|17|17|0|46
Python|1|7|11|46
Pascal|1|9|0|41
Prolog|1|3|0|30
--------|--------|--------|--------|--------
SUM:|15564|817782|1031983|4261959

Linux kernel in 2007
cloc|github.com/AlDanial/cloc v 1.86  T=33.42 s (573.1 files/s, 222933.2 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|8881|789631|867523|4070889
C/C++ Header|8325|176017|274768|924815
Assembly|917|35088|77163|179193
make|895|4276|5246|13610
XML|19|1469|87|12287
Perl|13|502|629|3212
yacc|4|401|273|2632
Bourne Shell|43|342|1000|2195
C++|5|242|150|1611
lex|4|167|196|1170
TeX|1|108|3|911
Glade|1|56|0|592
HTML|2|58|0|367
Python|4|72|85|317
NAnt script|1|86|0|263
Scheme|1|63|0|218
Objective C++|1|55|0|189
TNSDL|1|38|0|162
ASP|1|33|0|136
awk|2|14|7|98
Clojure|24|18|0|63
Bourne Again Shell|3|8|29|52
SWIG|5|5|3|51
Pascal|1|9|0|41
Prolog|1|3|0|30
XSLT|1|0|1|6
--------|--------|--------|--------|--------
SUM:|19156|1008761|1227163|5215110

Linux kernel in 2009
cloc|github.com/AlDanial/cloc v 1.86  T=44.67 s (531.8 files/s, 222371.1 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|11435|1072184|1141812|5487608
C/C++ Header|10033|232494|368949|1256624
Assembly|1021|35596|80843|183639
make|1088|4861|5422|16694
XML|27|1538|99|13827
Perl|25|1431|1648|7444
yacc|5|447|318|2962
Bourne Shell|50|464|1232|2922
SVG|1|0|1|2910
C++|3|224|105|1555
lex|5|222|246|1399
TeX|1|108|3|911
Glade|1|56|0|592
Python|6|114|157|463
INI|1|2|0|412
HTML|2|58|0|378
NAnt script|1|85|0|299
Bourne Again Shell|4|55|22|265
Scheme|1|63|0|218
Objective C++|1|55|0|189
TNSDL|1|38|0|162
ASP|1|33|0|136
Pascal|2|25|0|116
Clojure|32|19|0|102
awk|2|14|7|98
sed|1|0|3|29
reStructuredText|1|18|0|24
XSLT|1|0|1|7
diff|1|3|8|7
--------|--------|--------|--------|--------
SUM:|23753|1350207|1600876|6981992

Linux kernel in 2011
cloc|github.com/AlDanial/cloc v 1.86  T=59.51 s (526.0 files/s, 220771.7 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|15322|1430020|1473938|7373311
C/C++ Header|13076|303878|514987|1576537
Assembly|1176|39188|90358|200567
XML|148|5108|1104|55924
make|1345|5889|6477|22071
Perl|39|2532|2380|12189
Bourne Shell|59|562|1404|3388
yacc|5|455|322|2993
Python|18|440|297|1768
C++|3|228|104|1580
lex|5|222|246|1400
SVG|2|0|2|1045
TeX|1|108|3|911
awk|8|90|79|714
Glade|1|58|0|603
Bourne Again Shell|28|89|55|440
HTML|2|58|0|378
NAnt script|1|86|0|319
Scheme|1|63|0|218
Clojure|46|26|0|198
Objective C++|1|55|0|189
TNSDL|2|33|0|140
ASP|1|33|0|137
Pascal|2|26|0|121
XSLT|6|13|27|70
sed|1|0|3|30
vim script|1|3|12|27
reStructuredText|1|18|0|24
--------|--------|--------|--------|--------
SUM:|31301|1789281|2091798|9257292

Linux kernel in 2013
cloc|github.com/AlDanial/cloc v 1.86  T=84.25 s (485.4 files/s, 212340.4 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|20788|1991613|1883487|10193657
C/C++ Header|16258|389613|663461|2170426
Assembly|1379|46896|109064|240087
XML|198|5837|454|79207
make|1918|7469|7473|31253
Perl|40|4084|3192|20062
Bourne Shell|140|1371|2673|7797
Python|28|932|1072|6500
yacc|8|645|361|4299
PO File|5|791|918|3061
lex|8|279|278|1750
C++|3|228|104|1588
SVG|5|0|2|1387
Bourne Again Shell|39|200|182|1134
TeX|1|108|3|911
awk|8|96|88|746
Glade|1|58|0|603
HTML|2|58|0|378
NAnt script|1|89|0|337
Pascal|3|49|0|231
Scheme|1|63|0|218
Objective C++|1|55|0|189
Clojure|48|17|0|166
TNSDL|2|33|0|140
m4|1|15|1|95
XSLT|6|13|27|70
sed|1|0|3|30
vim script|1|3|12|27
reStructuredText|1|10|0|11
Windows Module Definition|1|0|0|8
--------|--------|--------|--------|--------
SUM:|40896|2450625|2672855|12766368

Linux kernel in 2015
cloc|github.com/AlDanial/cloc v 1.86  T=71.38 s (506.7 files/s, 216876.7 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|17985|1699464|1684681|8777946
C/C++ Header|14772|343696|588887|1850735
Assembly|1302|42409|100144|219751
XML|189|5491|483|71987
make|1648|6703|6933|26658
Perl|42|3601|2871|16754
Bourne Shell|78|874|1837|4821
yacc|7|557|341|3552
Python|25|707|505|3105
PO File|5|791|918|3061
C++|3|227|104|1583
lex|7|258|253|1575
SVG|5|0|2|1387
TeX|1|108|3|911
awk|8|89|88|720
Glade|1|58|0|603
Bourne Again Shell|33|89|69|541
NAnt script|1|96|0|382
HTML|2|58|0|378
Pascal|3|49|0|231
Scheme|1|63|0|218
Objective C++|1|55|0|189
Clojure|40|27|0|184
TNSDL|2|33|0|140
ASP|1|33|0|137
m4|1|15|1|84
XSLT|6|13|27|70
sed|1|0|3|30
vim script|1|3|12|27
reStructuredText|1|10|0|11
Windows Module Definition|1|0|0|7
--------|--------|--------|--------|--------
SUM:|36173|2105577|2388162|10987778

Linux kernel in 2017
cloc|github.com/AlDanial/cloc v 1.86  T=105.17 s (448.8 files/s, 202014.9 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|24009|2325704|2122457|11828872
C/C++ Header|18160|445028|766863|2951126
Assembly|1447|48693|114276|246941
JSON|108|0|0|79336
reStructuredText|664|29968|31491|57004
make|2267|8481|7963|35649
SVG|31|42|832|29991
Perl|51|5309|3930|28047
XML|24|1319|44|13650
Bourne Shell|220|2434|3681|13004
Python|63|1928|2376|10721
yacc|8|657|355|4350
HTML|2|458|0|3979
PO File|5|791|918|3061
lex|8|301|300|1902
C++|9|306|118|1897
Bourne Again Shell|46|382|314|1678
awk|11|142|135|1213
Markdown|1|220|0|1077
TeX|1|108|3|911
Glade|1|58|0|603
NAnt script|2|155|0|579
Pascal|3|49|0|231
Scheme|1|63|0|218
Objective C++|1|55|0|189
Cucumber|1|28|49|153
TNSDL|2|33|0|140
Clojure|39|10|0|101
m4|1|15|1|95
XSLT|6|13|27|71
CSS|1|14|23|35
vim script|1|3|12|27
sed|3|2|30|21
Windows Module Definition|1|0|0|8
--------|--------|--------|--------|--------
SUM:|47198|2872769|3056198|15316880

Linux kernel in 2019
cloc|github.com/AlDanial/cloc v 1.86  T=120.72 s (428.3 files/s, 203056.2 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|26629|2636300|2297947|13421521
C/C++ Header|19168|499599|920566|3748614
Assembly|1324|47238|105061|229629
JSON|213|0|0|137286
reStructuredText|1068|53392|45033|128313
make|2442|8984|9604|39367
SVG|54|117|1364|35878
Bourne Shell|453|8528|7032|35031
Perl|54|5413|4000|27388
Python|116|3691|4046|19934
HTML|5|656|0|5440
yacc|9|697|376|4616
PO File|5|791|918|3061
YAML|23|320|274|2281
lex|8|330|321|2004
C++|10|309|129|1912
Bourne Again Shell|51|352|318|1722
awk|11|170|155|1386
TeX|1|108|3|915
Glade|1|58|0|603
NAnt script|2|143|0|540
Markdown|2|133|0|423
Cucumber|1|28|49|166
TNSDL|2|33|0|140
Clojure|39|11|0|104
Windows Module Definition|2|14|0|102
m4|1|15|1|95
CSS|1|27|28|72
XSLT|5|13|26|61
vim script|1|3|12|27
Ruby|1|4|0|25
INI|1|1|0|6
sed|1|2|5|5
--------|--------|--------|--------|--------
SUM:|51704|3267480|3397268|17848667

Linux kernel in 2021
cloc|github.com/AlDanial/cloc v 1.86  T=143.06 s (423.5 files/s, 200157.7 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|29688|2955922|2393133|15054704
C/C++ Header|21421|603021|1065758|4999851
reStructuredText|2722|134271|55685|373596
Assembly|1289|46236|99105|224891
JSON|294|2|0|167085
YAML|1452|24897|6633|110700
Bourne Shell|703|18997|12990|73895
make|2617|9989|11033|44928
SVG|59|78|1159|37555
Perl|61|6991|4838|35312
Python|125|5535|5070|28383
yacc|9|695|355|4761
PO File|5|791|918|3077
lex|9|351|304|2152
C++|10|349|138|1934
Bourne Again Shell|51|297|247|1304
awk|10|149|119|1086
Glade|1|58|0|603
NAnt script|2|143|0|545
Cucumber|1|28|50|175
TNSDL|2|33|0|140
Clojure|40|7|0|113
Windows Module Definition|2|15|0|109
m4|1|15|1|95
CSS|1|28|29|80
XSLT|5|13|26|61
vim script|1|3|12|27
Ruby|1|4|0|25
INI|1|1|0|6
sed|1|2|5|5
--------|--------|--------|--------|--------
SUM:|60584|3808921|3657608|21167198

Linux kernel in 2023
cloc|github.com/AlDanial/cloc v 1.86  T=177.74 s (384.1 files/s, 190524.9 lines/s)
--- | ---

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
C|32319|3276875|2579268|16885292
C/C++ Header|23476|704241|1338922|6930983
reStructuredText|3301|160598|64371|438161
JSON|508|2|0|360081
YAML|3151|57691|14530|265589
Assembly|1328|47811|101202|229945
Bourne Shell|900|27584|18996|108035
make|2803|10867|11820|49931
SVG|74|90|1171|48177
Perl|66|7383|5033|36556
Python|157|6813|6354|33942
Rust|37|948|5454|5539
yacc|9|700|409|4914
PO File|6|948|1088|3733
lex|9|346|309|2111
C++|10|373|138|2022
Bourne Again Shell|56|392|322|1603
awk|13|217|157|1323
Glade|1|58|0|603
NAnt script|2|154|0|545
Cucumber|1|34|58|196
TeX|1|6|74|156
TNSDL|2|33|0|140
Windows Module Definition|2|15|0|110
CSS|3|38|49|104
m4|1|15|1|95
Clojure|31|0|0|73
XSLT|5|13|26|61
MATLAB|1|17|37|35
vim script|1|3|12|27
Markdown|1|8|0|25
Ruby|1|4|0|25
INI|1|1|0|6
sed|1|2|5|5
TOML|1|1|9|2
--------|--------|--------|--------|--------
SUM:|68279|4304281|4149815|25410145


### Zadanie 2
To wszystko w ~/.bashrc , po tym komenda source ~/.bashrc
```bash 
### na zajeciach z mana wytlumaczyc

    -l - wypisanie wszystkich danych w kolumnach (long listing format),
    -A - wypisanie prawie wszystkich plików, oprócz . (bieżący katalog) oraz .. (katalog niższy),
    -F - dopisanie znaków takich jak *, /, =, >, @, | do odpowiednich wpisów (np. / do katalogów),
    -b - wypisywanie stringów ze znakiem ucieczki (ang. escape character), czyli z \. Polega to na tym, że pliki i katalogi wieloczłonowe są zapisywane w stylu folder\ testowy, a nie 'folder testowy' (backslash przed spacją, brak apostrofów "opakowujących" string),
    -h - wypisywanie rozmiarów w łatwy do odczytania sposób, np. 254M, 3G,
    -v - sortowanie po wersjach



    -X - wyłącza wysyłanie termcapa przy inicializacji i deinicjalizacji stringów do terminala, dzięki czemu nieporządane akcje, takie jak czyszczenie ekranu, nie są wykonywane.
    -E - sprawia, że less automatycznie się kończy po pierwszym napotkaniu EOF,
    -R - sprawia, że znaki surowe (ang. raw) są wyświetlane, ale w przeciwieństwie do -r, wyświetla jeszcze kolory


alias ll='ls -lAFbhv --color=always | less -XER'

# + daje polaczenie stringa, reszta to jakies formaty daty
# (+ ozancza ze chcemy formatowac w opisany sposob)
alias gentmp='date +tmp-%Y%m%d%H%M%S'

# -d usuwa itemki ktorych nie ma w secie w ciapkach
# -c usuwa dopełnienie setu, czyli to co chcemy ( bo -d zostawia tylko
# dopełnienie), przekierowanie z urandom i 32 chary, echo dla entera
alias genpwd='tr -dc '3-9A-HJ-NP-Z' < /dev/urandom | head -c 32; echo'


```
### Zadanie 3
grep print lines that match patterns

przykladowe falgi

    -i - ignorowanie wielkości znaków w tekście, a więc szukając wzorca bar, pokażą się nam również wyszukane fragmenty bAr, BAR, bAR, itd.
    -w - szukanie jedynie całych wyrazów, więc gdy szukamy wzorca bar, a w tekście znajdują się fragmenty barfoo, foobar, fobaro, bar, to wyszukamy tylko bar. Możemy skorzystać z egrep z tą samą funkcją, aby wyszukać alternatywy dwóch słów, np. bar|foo,
    -n - poprzedzenie każdego zwróconego wyniku numerem linii, w której jest szukany wzorzec,
    -v - odwrócenie szukanego wzorca, więc jeśli wpiszemy wzorzec bar, to pokaże nam wszystkie wyniki, w których tego wzorca nie znajdziemy,
    -r - wyszukanie wzorca rekursywnie, w bieżącym katalogu jak i wszystkich podkatalogach. Jeśli w katalogu znajdują się dowiązania symboliczne i również w nich chcemy przeszukiwać zawartość, to możemy skorzystać z opcji -R.
    
Zbiór wybranych znaków można zapisać w nawiasach kwadratowych, np. [ABCDEF] sprawi, że będziemy szukać jednoznakowego wzorca

Najczęściej używane zbiory mają jednak predefiniowane aliasy, takie jak [:alnum:]

przykladowe operatory potworzen
```
? - zbiór jest opcjonalny, a jeśli wystąpi, to tylko raz,
* - zbiór może wystąpić dowolną ilość razy (nawet zero),
+ - zbiór musi wystąpić co najmniej raz,
```

(/etc/locale.alias zawira mapowanie - pierwszy element to alias lokalizacji, a drugi element to nazwa pliku konfiguracyjnego)

1. -w only whole word matching
```
grep -w "polish" /etc/locale.alias 
```
da tylko polski jezyk
2. -x whole line matching

3. -n daje numery w których regex występuje
```
grep -n "^po.*" /etc/locale.alias 
```
wyswietli linijki i zaczynajace sie od po języki

4. -A n, -B n - kolejno kontekst przed i po n linijkach
```
grep -B 3 -A 3 -n "^po.*" /etc/locale.alias 
```
to samo co wcześniej ale z 3 przed 3 po
5. -c daje count plikow spelniajacych regexa
```
grep -c "ISO" /etc/locale.alias 
grep -c "JP" /etc/locale.alias 
```
6. WAZNE -v invert!

6. grep -v inverted search, nie to co szukamy
btw locale.alias to mapowanie z nazw zwyklych na ISO(?)

### Zadanie 4

find z regexem
find wyszukuje pliki w danym directory, zazwyczaj z grepem mozna ale

przykladowe kryteriami selekcji:
```
-name - wyszukuje plik o określonej nazwie,
-size - wyszukuje pliki o danej wielkości,
-type - wyszukuje pliki o wybranym typie: d to katalog, f to plik normalny, b to plik blokowy, c to plik znakowy, a l to dowiązanie symboliczne,
```
```
# wyszukuje katalogi 
find . -type d
```

Ze znalezionymi plikami można akcje np.
```
find . -name 'test*' -print
```
#
```bash
find . -regextype sed -regex ".*[a-f0-9\-]\{36\}\.jpg"
```
takie cos tez działa
```bash
# wyszukuje na desktopie rekursywnie pdfy
1. find ~/Desktop/ | grep ".*\.pdf$"
```
2. -type [psdf] - wyszukuje pliki f - zwykle
p - pipe, s - socket, d- directories
```bash=
# znajduje pliki na desktopie będące directory które są lista
find ~/Desktop/ -type d -name ".*lista.*"
```
3. -perm mode wyszukuje pliki o danym mode
```bash=
# wszystkie z 777 uprawnieniami
find ~ -perm 777 | grep "windows"
```
4. -size [+-]size, + wieksze - mniejsze
```
find ~/Desktop/ -size +100M
```
5. -mtime [+-]n pliki zmodyfikowane w czasie - do n + n wzwyz
```
find ~/Desktop/ -mtime -3
find ~/Desktop/ -mtime +1200
# starsze niz 1200 dni

```

### Zadanie 5
```
przykladowe flagi
-v - pokaż, w których plikach została zmieniona nazwa,
-n - nie rób żadnych zmian, jedynie wypisz nazwy plików, których nazwa powinna zostać zmieniona, ale tej nazwy nie zmieniaj,

poczatek wzorca:
s - jak zamiana 
y - jak translacja (np. duze litery na male - 'y/A-Z/a-z/')
```
rename - renames multiple files
rename [options] 's/old_pattern/new_pattern/' files
```bash=
for i in {0..30};do touch plik$i.txt;done # tworzy 31 plikow txt
rename "s/\.txt$/.csv/" *.txt         
#zamieniamy .txt na .csv konczace sie na .txt
```

### Zadanie 6

#### Listę zainstalowanych pakietów, które nie posiadają własnego podkatalogu w /usr/share/doc/.
##### `dpkg`

`dpkg` is a medium-level tool to install, build, remove and manage Debian packages.
`dpkg` itself is controlled entirely via command line parameters, which consist of exactly one action and zero or more options. The action-parameter tells dpkg what to do and options control the behavior of the action in some way.

           -l, --list package-name-pattern...
               List packages matching given pattern.
               
Jeśli pierwsze dwa znaki w kolumnie są "ii", oznacza to, że pakiet jest zainstalowany.

Jeśli pierwsze dwa znaki są "rc", oznacza to, że pakiet został usunięty, ale pozostawił po sobie konfigurację.

itd. itp. nie ma tego w manualu jak coś

##### `grep '^ii'`

To znaczy, że zwracane są linijki które zaczynają się od `ii`.

##### `awk {$print 2}`
       awk - pattern scanning and processing language
To znaczy, że wypisuje drugie słowo na podstawie separacji spacjami
##### `while read -r filename; do [ -e "/usr/share/doc/$filename" ] && echo "$filename"; done`

`read -r` jest w BASH(1) - wyszukać `read\[`
bierze linijkę z stdin bez interpretacji znakow `-r` i wynik zapisywany jest w filename. Dopóki stdin niepusty sprawdzane jest czy istnieje (`-e` - TEST(1)) plik w katalogu i wypisywana jest nazwa 

odp.:
```
dpkg -l | grep '^ii' | awk '{print $2}' | while read -r filename; do [ -e "/usr/share/doc/$filename" ] && echo "$filename"; done
```

inny sposób
```
(dpkg -l | grep "^ii" | awk '{print $2}'; ls -l /usr/share/doc | awk '{print $9}') | sort | uniq -u
```
#### Listę podkatalogów katalogu /usr/share/doc/, których nazwy nie są nazwami żadnego zainstalowanego pakietu. Przy każdym z takich podkatalogów wypisz nazwę pakietu, który jest jego właścicielem

odp.:
```
for subdir in /usr/share/doc/*; do
	package_name=$(dpkg -S "$subdir" 2>/dev/null | awk '{print substr($1, 1, length($1)-1)}')

	if ! [ -z "$package_name" ]; then
		echo "Subdir: $subdir"
		echo "Owner: $package_name"
		echo
	fi
done

```

#### Listę pakietów posiadających własny podkatalog w katalogu /usr/share/doc/, który jednak nie zawiera pliku changelog.Debian.gz.

```
dpkg -l | grep '^ii' | awk '{print $2}' | while read -r filename; do [ -e "/usr/share/doc/$filename" ] && [ ! -e "/usr/share/doc/$filename/changelog.Debian.gz" ] && echo "$filename"; done

```
#### Listę pakietów posiadających własny plik changelog.Debian.gz, który zawiera tylko jeden wpis (zwykle Initial release)

PRAWDOPODOBNIE ŹLE BO NIC NIE ZNAJDUJE

```
dpkg -l | grep '^ii' | awk '{print $2}' | while read -r package; do [ -e "/usr/share/doc/$package" ] && [ $(zcat "/usr/share/doc/$package/changelog.Debian.gz" 2>/dev/null | wc -l) -eq 1 ] && echo "$package"; done

```

#### Liczbę wystąpień słowa bash (zapisanego małymi lub wielkimi literami) w pliku /usr/share/doc/bash/INTRO.gz

```
zgrep -oic 'bash' /usr/share/doc/bash/INTRO.gz

```
       -o, --only-matching
              Print only the matched (non-empty) parts of a matching line, with each such part on a separate output line.

       -i, --ignore-case
              Ignore case distinctions in patterns and input data, so that characters that differ only in case match each other.

ALTERNATYWA DLA 6
1.
```bash
for i in $(apt list | awk -F/ '{print $1}');do if ! test -f "usr/share/doc/$i";then echo $i;fi;     done;
```
2.
```bash=
$(apt list | awk -F/ '{print $1}' > installed_packages.txt)
 
 for dir in $(ls /usr/share/doc/); do
     if ! grep -Fxq "$dir" installed_packages.txt; then
         echo "$dir"
     fi
 done
 rm installed_packages.txt

```


3
```bash=
 path="/usr/share/doc"
 
 for i in $(ls $path)
 do
     if ! test -f $path/$i/changelog.Debian.gz; then
         echo $i
     fi
 done

```
4
```bash=
path="/usr/share/doc"

for i in $(ls $path)
do
    if test -f $path/$i/changelog.Debian.gz; then
        if [ $(ls $path/$i | wc -l) == 2 ]; then
            echo $i
        fi
    fi
done



```



### Zadanie 7

```bash
#1.
sudo find / |  grep ".*\.so\(\.[0-9]\+\)\?$"
#2
sudo find / -type l |  grep ".*\.so\(\.[0-9]\+\)\?$"
#3
# jest też \; różni się od + !
sudo find / -regextype sed -regex '.*\.so\(\.[0-9]\+\)\?$' -exec du {} + | awk '{total += $1; count++} END {print "total size:" total, "mean:" total/count}'
#4
sudo find / -regextype sed -regex '.*\.so\(\.[0-9]\+\)\?$' -exec dirname {} + | sort -u
#5
sudo find / -type l -regextype sed -regex '.*\.so\(\.[0-9]\+\)\?$' -exec dirname {} + | sort -u


```
### Zadanie 8
1. 
```bash
find /usr/share/locale -regextype sed -regex ".*\.mo$" | awk -F/ '{print $5}' | sort -u
```
2.
```bash
find /usr/share/locale -regextype sed -regex ".*dpkg.mo$" | awk -F/ '{print $5}' | sort -u
```
3.
```bash
find /usr/share/locale/pl/LC_MESSAGES/
```
4.
```bash=
 path="/usr/share/man"
 
 for i in $(ls $path | grep -v "^man[1-8]$")
 do
     echo "$i has:"
     for j in $(ls $path/$i)
     do
         echo $j
     done
 done
 
 echo "en has:"
 for i in $(ls $path | grep "^man[1-8]$")
 do
     echo $i
 done

```
5.
```bash
# mozna zauwazyc ze kazda strona konczy sie na *gz
find /usr/share/man/pl -type f -name "*.gz" | awk -F/ '{print $7}' | sed 's/\.gz$//'
```
### Zadanie 9
```
pierwszy argument to korzen, drugi to wzorzec - $0 to nazwa pliku, $1 to pierwszy itd

wywolanie: bash plik . "wzorzec"

ls -R "$1" > ls-R
echo "ls-R created."
echo ""

grep -n "$2" ls-R |
while IFS=: read -r number content; do
    if ! grep -q '[^\\]/' <<< "$content"; then
        dirpath=$(head -n "$number" ls-R | tac | grep -m 1 "^\./")
    	echo "$(echo "$dirpath" | awk '{print substr($0, 1, length($0)-1)}')/$content"
    	echo ""
	fi
done
```

alternatywa?
```bash
du -a $1 | awk '{print $2}' > ls-R
cat ls-R | grep $2
```

https://www.systutorials.com/docs/linux/man/1-mlocate/

locate is a Unix utility which serves to find files on filesystems. It searches through a prebuilt database of files generated by the updatedb command or by a daemon. It operates significantly faster than find, but requires regular updating of the database. This sacrifices overall efficiency (because of the regular interrogation of filesystems even when no user needs information).

locate - database is world-readable, so the index is built as an unprivileged user

mlocate - use a restricted-access database, only showing filenames accessible to the user


updatedb - updatedb creates or updates a database used by locate(1).  If the data base already exists, its data is reused to avoid rereading  directories that have not changed. Updatedb is usually run daily from a systemd.timer(8) to update the de fault database.



Biblioteka KPathSea jest częścią systemów TeXowych, takich jak TeX Live czy MiKTeX. Zapewnia mechanizmy wyszukiwania plików, które są niezbędne podczas kompilacji dokumentów w formacie TeX. Kluczowym narzędziem w bibliotece KPathSea jest polecenie kpsewhich, które umożliwia efektywne znajdowanie lokalizacji plików używanych przez TeXa. 

Systemy TeXowe to zestawy oprogramowania np. LaTeX jest to zestaw makr i stylów budujących na bazie TeXa.

https://tex.stackexchange.com/questions/492093/what-does-kpsewhich-stand-for

https://tug.org/texinfohtml/kpathsea.html#Searching-overview

kpathsea stara sie krzystac z baz danych i omijac tym samym rekurencyjne przeszukiwanie. Jest to wazne np. przy kompilowaniu dokumnetów LaTeX, gdzie uzywanych jest wiele bibliotek, które odwołują się do znacznej liczby innych bibliotek. 



### Zadanie 10
Przykładowy tekst:
asdf ds asd dfsda sd asdf asdf fa sdfb asdf

sed - modyfikacja strumieni tekstow
sed 's/asdf/X/g' zad10.txt podmieni wszystkie asdf
sed 's/asdf/X' zad10.txt podmieni pierwsze asdf
sed -e 's/asdf/X/g' -e 's/ds/Y/g' zad10.txt wiele podmianek
sed 's/asdf/X/3' tylko 3 np

### Zadanie 11
sedscript
```bash 
s/RG\|GR/BB/
t exit
s/RB\|BR/GG/
t exit
s/GB\|BG/RR/
:exit
```

Skrypt usesed.sh
```bash 
#!/bin/bash

TXT1=$1
TXT2=$TXT1
TEST=true

while [ $TEST ]; do
    TXT2=$(echo "$TXT1" | sed -f sedscript)
    echo $TXT2
    sleep 1
    if [ "$TXT2" != "$TXT1" ]; then
        TXT1=$TXT2
    else
        TEST=false
    fi
done
```

Użycie:
sh usesed.sh DANE

Skrypt nie dopasowuje wszystkich wzorców na raz tylko szuka dopasowań do wzorców w takiej kolejności w jakiej występują one w sedscript - niezgodnie z poleceniem.