ssh worm "ssh air 'cd run && ./combiner.sh'"
rsync -zrtv --progress --include='/data.txt' --include='/settings.txt' --exclude='*' --rsync-path="ssh air rsync" solo4857@wormulon.cs.uidaho.edu:/home/solomon/run/ . 
