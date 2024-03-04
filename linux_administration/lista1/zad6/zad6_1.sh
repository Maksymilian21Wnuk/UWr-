for i in $(apt list | awk -F/ '{print $1}');do if ! test -d "usr/share/doc/$i";then echo $i;fi;done;

