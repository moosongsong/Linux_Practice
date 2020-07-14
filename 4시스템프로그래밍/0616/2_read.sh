#!/bin/bash

# ./2.sh filename
# $0     $1

# 1. 리다이렉션 사용
# while read line; do	# read 명령어는 라인 단위로 입력을 받습니다.
# 	echo "$line"
# done < "$1"

# 2. 파이프라인
# cat "$1" | while read line; do
# 	echo "$line"
# done


# while read name age; do
# 	echo "name: $name, age: $age"
# done < person.txt


read a b
echo $a
echo $b





























