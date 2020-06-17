#!/bin/bash

# int fact(int n) {
#   if (n <= 1)
#     return 1;
#   //return n * fact(n - 1);
#   int temp = fact(n - 1)
#   return n * temp;
# }

fact() {		
	if (($1 <= 1)); then
		echo 1
	else
		local temp=$(($1 - 1))
		local result=$(fact $temp)
		echo $((result * $1))
	fi
}

echo $(fact 5)
