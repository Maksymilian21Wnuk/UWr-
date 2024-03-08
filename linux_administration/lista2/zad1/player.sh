#!/bin/bash

OIFS="$IFS"
IFS=$'\n'

echo "Give me a path to mp3 folder: "
read -r path

# It's good practice to double-quote variables to preserve spaces and prevent globbing and word splitting.
mp3files=$(find $path -type f -name '*.mp3' -print0 | xargs -0 -I {} echo '{}')

mp3array=()

for file in $mp3files;do
    echo $file
    res=$(id3v2 -l $file | grep -E "Title|Album")
    title=$(echo "$res"| grep -oP 'Title\s*:\s*\K.*?(?=\s+Artist)')
    album=$(echo "$res" | grep -oP 'Album\s*:\s*\K.*?(?=\s+Year)')
    genre=$(echo "$res" | grep -oP 'Genre\s*:\s*\K.*?(?=\s+\(\d+\))')
    echo $title $album $genre
    mp3array+=($title $album $genre)

done



IFS="$OIFS"

select file in "${mp3array[@]}"; do
    if [ "$REPLY" -gt 0 ] && [ "$REPLY" -le "${#mp3array[@]}" ]; then
        echo "Playing: $file"
        mplayer $file
        break
    else
        echo "Invalid option. Please select a number between 1 and ${#mp3array[@]}"
    fi
done

