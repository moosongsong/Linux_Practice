#!/bin/bash

# str="global"			# const char* str = "global"
# 
# func() {				# void func() {
# 	local str="local"	#   const char* str = "local"
# 	echo $str			#   puts(str);
# }						# }
# 
# func
# read
# echo $str



# func() {
# 	# 함수 내에서 local 없이 생성된 변수는 전역 변수로 취급됩니다.
# 	str="local"
# }			
# 
# echo $str	# 변수가 없으므로 아무런 값이 출력되지 않습니다.
# func
# read
# echo $str	# func에서 만들어진 변수를 사용합니다.

# function foo {
# 	command
# }

# bash에서 함수는 진짜 함수가 아니므로 매개변수를 가질 수 없습니다.
# foo(x, y) {
foo() {
	# 전될된 인자는 위치 매개변수에 저장됩니다.
	echo $1
	echo $2
}

# 함수 호출 시, 인자 전달은 명령행에서 인자를 전달하는 것과 동일하게 수행하면 됩니다.
#   $1    $2
foo hello world


























