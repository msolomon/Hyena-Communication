#! /bin/sh
echo $0
trials=$1

hyenadir=`dirname $0`
#hyenadir=`pwd`/../../$hyenadir

count=0
until [ $count -ge $trials ]
do
	count=$(( $count + 1 ))
	$hyenadir/qthyena $count
done

# now combine into one file
$hyenadir/combiner.sh
