#! /bin/bash

while [ -n "$(echo "$1" | grep '-')" ] ; do
	case "$1" in
		-a) echo "option a";;
		-b) echo "option b";;
		-c) echo "option c";;
		*) echo "usage: ./test.sh [-a] [-b] [-c]"
			exit 1;;
	esac
	shift
done
