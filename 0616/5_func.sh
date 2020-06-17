#!/bin/bash

# foo() {
# 	echo "매개변수 갯수: $#"
# 	for arg in $@; do
# 		echo "$arg"
# 	done
# }
# 
# foo hello world goodbye
# 
# name1=daniel
# name2=susan
# foo $name1 $name2


foo() {
	# return 10	# 함수의 종료 상태를 설정하기 위한 명령어
	# echo 10
	# echo 3.14
	echo hello
}

#ret=foo
# echo $ret	# 10
ret=$(foo)
echo "ret: $ret"




















