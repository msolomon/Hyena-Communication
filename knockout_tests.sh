#! /bin/bash

# run knockout gene tests for all combinations in below list

for c in '' 'landmark' 'landmark, named' 'landmark, named, number_calling'  'landmark, number_calling' 'named' 'named, number_calling' 'number_calling'
do
        d="s/KNOCKOUT_OPS\[] \= {/KNOCKOUT_OPS\[] \= {$c,/"
        sed "$d" template.h | sed 's/,}/}/g' | sed 's/{,/{/g' > globals.h
        qmake
        make -j4
        if [[ $c == '' ]]
        then
                name='all-on'
        else
                name=`echo $c | sed 's/, /-no-/g' | sed 's/^/no-/' | sed 's/_/-/g'`
        fi
        ./deploy.sh $name
done
