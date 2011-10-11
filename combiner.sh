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
bzip2 data.txt
du -h data.txt.bz2


echo Combining `find | grep final_ | wc -l` files...
first=1
for f in final_*
do
        if [ $first -eq 1 ]
        then
                head -n 1 $f > final.txt
                first=0
        fi
        tail --lines=+2 $f >> final.txt
done

du -h final.txt
bzip2 final.txt
du -h final.txt.bz2


echo Combining `find | grep knockout_ | wc -l` files...
first=1
for f in knockout_*
do
        if [ $first -eq 1 ]
        then
                head -n 1 $f > knockout.txt
                first=0
        fi
        tail --lines=+2 $f >> knockout.txt
done

du -h knockout.txt
bzip2 knockout.txt
du -h knockout.txt.bz2
