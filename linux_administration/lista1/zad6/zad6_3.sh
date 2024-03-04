path="/usr/share/doc"

$(apt list | awk -F/ '{print $1}' > installed_packages.txt)

for dir in $(ls /usr/share/doc/); do
     if grep -Fqx "$dir" installed_packages.txt; then
         if ! test -f $path/$dir/changelog.Debian.gz; then
             echo $dir
         fi
     fi
done
rm installed_packages.txt

