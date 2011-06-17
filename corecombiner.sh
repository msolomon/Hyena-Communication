#! /bin/sh
fnames=`find . -mindepth 2 -name 'data.txt'`
isfirst=true

echo 'Combining data files...'
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

echo 'Done.'
