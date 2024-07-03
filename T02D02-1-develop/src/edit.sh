#!bin/bash/

if [[ ${#} == 3 ]];
then
    if [[ $2 == $3 ]];
    then
        echo "Incorrect input"
    else

        sed -i "" "s/$2/$3/g" $1

        size=$(wc -c $1 | awk '{print $1}')
        date=$(date -r $1 "+%Y-%m-%d %H:%M")
        sha=$(shasum -a '256' $1 | awk '{print $1}')
        
        echo "$1 - $size - $date - $sha - sha256"
        echo "$1 - $size - $date - $sha - sha256" >> files.log
    fi
else
    echo "Incorrect input"
fi