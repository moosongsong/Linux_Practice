#!/bin/bash

# ./a.sh -a -b -c
# while [ -n "$(echo $1 | grep '-')" ]; do 
# 	case $1 in
# 		-a) echo "option a";;
# 		-b) echo "option b";;
# 		-c) echo "option c";;
# 		*) echo "usage: a.sh [-a] [-b] [-c]"
# 			exit 1;;
# 	esac
# 	shift
# done


# ./a.sh -a -b -c
# getopts: 계속 처리해야 할 옵션이 있으면 종료 코드를 0으로 설정하고
# 처리할 옵션이 없으면 종료 코드를 1로 설정합니다.
# while getopts ":abc" opt; do
# 	#          ^--- 옵션 스트링에 없는 옵션이 사용될 경우, 오류 출력 금지 문자!
# 	case "$opt" in
# 		a) echo "option a";;
# 		b) echo "option b";;
# 		c) echo "option c";;
# 		\?) echo "usage: a.sh [-a] [-b] [-c]"	# 다른 옵션이 들어온 경우, ?로 설정됨
# 			exit 1;;
# 	esac
# done


# ./a.sh -a -b a.txt -c
while getopts ":ab:c" opt; do
	#             ^-- 특정 옵션에 대한 인자를 처리하기 위한 문자
	case "$opt" in
		a) echo "option a";;
		b) echo "option b $OPTARG";;
		c) echo "option c";;
		\?) echo "usage: a.sh [-a] [-b filename] [-c]"
			exit 1;;
	esac
done


















