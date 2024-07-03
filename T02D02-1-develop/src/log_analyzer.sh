#!bin/bash/

if [[ ${#} == 1 ]];
then
    numberOfRecords=$(wc -l $1 | awk '{print $1}')
    numberOfUniqueFiles=$(awk 'a[$1] == "" {a[$1]="X"} END {print length(a)}' $1)
    numberOfChanges=$(cat $1 | cut -f 8 -d ' ' | tail -n+2 | wc -l | awk '{print $1}')

    echo "$numberOfRecords $numberOfUniqueFiles $numberOfChanges"
else
    echo "Incorrect input"
fi