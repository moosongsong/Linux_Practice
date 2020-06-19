#! /bin/bash
cnt=0
sum=0

while true; do
	((++cnt))
	if((cnt>100)); then
		break	
	fi

	if(( (cnt % 2) !=0));then
		continue
	else 
		((sum+=cnt))
	fi
done

echo "$sum"





