#! /bin/bash

for top in su mo tu we th fr sa ; do
#	echo -n "$top"
	printf " %s" $top
done
echo

for var in { 1 .. 31 } ; do
	printf " %2d" $var
	if [[$var%7 = 0]];then
		echo
	fi
done
