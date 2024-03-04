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

