#! /bin/sh
echo $0
cores=1
trials=1
if [ $# -gt 0 ]
then
	cores=$1
fi
if [ $# -gt 1 ]
then
	trials=$2
fi

hyenadir=`dirname $0`
hyenadir=`pwd`/$hyenadir

count=0
until [ $count -ge $cores ]
do
	count=$(( $count + 1 ))
	mkdir -p cores/$count
	if [ ! -e cores/$count/combiner.sh ]
	then
		ln -s $hyenadir/combiner.sh cores/$count/combiner.sh
	fi
	cd cores/$count
	$hyenadir/trials.sh $trials &
	cd ../..
done
