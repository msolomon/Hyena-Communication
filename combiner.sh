#! /bin/sh
head -n 1 data_1.txt > data.txt
for f in data_*
do
	tail --lines=+2 $f >> data.txt
done

