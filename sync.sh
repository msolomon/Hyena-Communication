#rsync -rtv --exclude='ui_*' --exclude='moc_*' --include='*.sh' --include='*.ui' --include='*.cpp' --include='*.h' --include='*.pro' --exclude='*' . solo4857@wormulon.cs.uidaho.edu:/home/solo4857/qthyena
rsync -rtv --exclude='ui_*' --exclude='moc_*' --exclude='*.o' --include='*.sh' --include='*.ui' --include='*.cpp' --include='*.h' --include="*.c" --include='Makefile' --include='*.pro' --exclude='*' --rsync-path="ssh air rsync" . solo4857@wormulon.cs.uidaho.edu:/home/solomon/qthyena
