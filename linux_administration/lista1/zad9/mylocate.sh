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
