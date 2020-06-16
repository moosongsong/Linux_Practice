#!/bin/bash

# test

# 비밀번호를 확인하는 프로그램
# read -p "input password: "
# if [ -z "$REPLY" ]; then
# 	echo "비밀번호를 입력하지 않으셨습니다."
# 	exit 1
# fi
# 
# read -p "confirm your password: " pswd
# if [ "$pswd" = "$REPLY" ]; then		# if (strcmp(pswd, REPLY) == 0) {
# 	echo "OK!"
# else
# 	echo "wrong password"
# fi


# test
# filename="./if.sh"
# if [ -e "$filename" ]; then
# 	echo "해당 파일이 존재합니다."
# else
# 	echo "해당 파일은 존재하지 않습니다."
# fi


# test
# 특정 디렉터리가 존재하지 않을 경우, 그 디렉터리를 생성하는 코드를 생각해 봅시다.
# dirname="mysub"
# if [ ! -d "$REPLY" ]; then
# 	mkdir "$dirname"
# fi


# dirname="subdir"
# [ -d "$dirname" ] || mkdir "$dirname"

read -p "input number: "	# -20,  300, 300 0, 070
if [[ ! "$REPLY" =~ ^-?[[:digit:]]+$ ]]; then
	echo "input data is not number"
fi

if [ "$REPLY" -eq 0 ]; then
  echo "zero"			
else				
  echo "not zero"
fi				















