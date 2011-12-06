#! /bin/sh

## Set up
thisdir=`pwd`
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
if [ -e run-old ]
then
	rm -r run-old
fi
if [ -e run ]
then
	mv run run-old
fi

## Ensure the project is compiled with current files
echo "Building project..."
cd $hyenadir
qmake "CONFIG+=release"
# Link in tcmalloc if it exists
if [ -e "/usr/lib/libtcmalloc.so" ]
then
	echo Adding link to tcmalloc...
	sed -i "s/-lpthread/-lpthread -ltcmalloc/" Makefile
fi
make -j$cores
cd $thisdir
# Copy globals.h over so we know what settings were used
mkdir -p run
cp $hyenadir/globals.h run/settings.txt
# link copy script
ln -s $hyenadir/combiner.sh run/combiner.sh

## Run the trials on each core
echo "Beginning trials..."
echo "Output will go to run/status.txt (use tail -f to follow)"
count=0
until [ $count -ge $cores ]
do
	count=$(( $count + 1 ))
	cd run
	$hyenadir/trials.sh $trials $count & >> status.txt
	cd ..
done
