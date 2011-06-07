#! /bin/sh
fnames=`find . -mindepth 1 -name 'data.txt'`
isfirst=true


for f in $fnames
do
	if $isfirst
	then
		head -n 1 "$f" > data.txt
		isfirst=false
	fi
	echo "$f"
	tail --lines=+2 "$f" >> data.txt
done
