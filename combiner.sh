#! /bin/sh

echo Combining `find | grep data_ | wc -l` files...
first=1
for f in data_*
do
        if [ $first -eq 1 ]
        then
                head -n 1 $f > data.txt
                first=0
        fi
        tail --lines=+2 $f >> data.txt
done

du -h data.txt
