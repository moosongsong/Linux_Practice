#!/bin/bash

name=daniel

echo name		# name
echo $name		# daniel
echo "$name"	# daniel
echo '$name'	# $name
echo "'$name'"	# 'daniel'
echo \$name		# $name
echo ${name}	# daniel

echo "$namexxx"	# namexxx라는 변수는 없으므로 아무것도 출력되지 않습니다.
echo "$name"xxx	# danielxxx	ex) printf("%s""xxx", name);

# 명령어의 출력 결과를 변수에 저장할 수도 있습니다.
result=$(date)	# result=`date`
echo "result: $result"
