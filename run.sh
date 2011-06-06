#! /bin/sh

## Set up
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

## Clear out old trial data
echo "Removing old data..."
if [ -e cores-old ]
then
	rm -r cores-old
fi
if [ -e cores ]
then
	mv cores cores-old
fi

## Ensure the project is compiled with current files
echo "Building project..."
qmake "CONFIG+=release"
make -j$cores
# Copy globals.h over so we know what settings were used
mkdir -p cores
cp $hyenadir/globals.h cores/settings.txt

## Run the trials on each core
echo "Beginning trials..."
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
