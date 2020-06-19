#! /bin/bash
dirname="mysub"

if [ -d "$dirname" ] ; then
	echo "there is"
else
	echo "make dif"
	mkdir "./$dirname"
fi
