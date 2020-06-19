#! /bin/bash
read -p "input integer: "

if [[ "$REPLY" =~[0-9]  ]] ; then
	echo "this is 0"
else
	echo "no"
fi
