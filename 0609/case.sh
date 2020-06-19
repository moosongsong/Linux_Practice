#! /bin/bash

clear

echo "
a. coffee
b. latte
c. cake
q. END
"

read -p "input menu number: "

clear

case $REPLY in 
	q|Q) exit 0;;
	a|A) echo "select coffee";;
	b|B) echo "select latte";;
	c|C) echo "select cake";;
	*) echo "wrong";;
esac
