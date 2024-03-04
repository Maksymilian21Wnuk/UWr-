#find /usr/share/locale -regextype sed -regex ".*\.mo$" | awk -F/ '{print $5}' | sort -u
#find /usr/share/locale -regextype sed -regex ".*dpkg.mo$" | awk -F/ '{print $5}' | sort -u
#find /usr/share/locale/pl/LC_MESSAGES/
#find /usr/share/man/pl -type f -name "*.gz" | awk -F/ '{print $7}' | sed 's/\.gz$//'
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
