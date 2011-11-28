#! /bin/bash

for dir in *
do
	cd $dir
	./run.sh $1 $2
	cd ..
	until (( `find $dir/run/data_* 2>/dev/null | wc -l` ==  `expr $1 \* $2` ))
	do
		sleep 10
	done
done
