#! /bin/sh
echo $0
trials=1
if [ $# -ne 0 ]
then
	trials=$1
fi

hyenadir=`dirname $0`
hyenadir=`pwd`/$hyenadir

count=0
until [ $count -ge $trials ]
do
	count=$(( $count + 1 ))
	mkdir -p trials/$count
	cd trials/$count
	$hyenadir/qthyena &
	cd ../..
done
