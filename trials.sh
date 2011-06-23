#! /bin/sh
trials=$1
corenum=$2

hyenadir=`dirname $0`
#hyenadir=`pwd`/../../$hyenadir

# Limit each trial to 2GB of memory and 1 hour CPU time
ulimit -d 2097152
ulimit -t 7200

count=0
until [ $count -ge $trials ]
do
	count=$(( $count + 1 ))
	echo Starting trial $(( $count + ( $trials * ($corenum - 1)) ))...
	# Run at lower priority
	nice -5 $hyenadir/qthyena $(( $count + ( $trials * ($corenum - 1)) )) >> status.txt
done

# now combine into one file
#$hyenadir/combiner.sh
