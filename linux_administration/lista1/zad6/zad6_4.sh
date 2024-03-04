path="/usr/share/doc"

for i in $(ls $path)
do
    if test -f $path/$i/changelog.Debian.gz; then
        if [ $(ls $path/$i | wc -l) == 2 ]; then
            echo $i
        fi
    fi
done

