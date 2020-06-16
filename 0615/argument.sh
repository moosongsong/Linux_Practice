#!/bin/bash

# in C
#           a.out hello world
#     argv: [0]   [1]   [2]
# int main(int argc, char** argv) {
# 	for (int i = 0; i < argc; i++)
# 		printf("argv[%d] = %s\n", argv[i]);
# }

#    c: argument
# bash: positional parameter

# pre-defined variable: ?, REPLY
#                       0 1 2 3 4 5 6 ...

# echo $0	# 실행된 스크립트의 이름

# 위치 매개변수 사용 시, 2자리수 이상의 매개 변수에 접근하려면
# 반드시 중괄호로 묶어 사용해야 합니다. :(
										# ./arguemtn.sh 1 2 3 4 5 6 7 8 9 10
# echo $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10}	# 1 2 3 4 5 6 7 8 9 10

# int main(int argc, char **argv)
#               ^           ^--- optional parameter
#               |
#               +---- #

# ++argv, --argc;


# ./argument.sh hello world
# echo $#	# 2, 스크립트 이름은 제외한 나머지의 개수만 전달됩니다.

# 연습 문제. 아래의 기능과 동일하게 동작하는 스크립트를 작성해 보세요 :D
# int main(int argc, char** argv) {
# 	for (int i = 1; i < argc; i++)
# 		printf("%s\n", argv[i]);
# }

# shift: 위치 매개변수 전체를 왼쪽으로 한칸 이동시킨다.
# ex)            ./argument hello world
#                                 0     1     2

# 1. while + shift
# while [ -n "$1" ]; do	# while ($1 != NULL) {
# 	echo "$1"
# 	shift
# done

# 2. for + @(위치 매개변수 전체를 저장하고 있는 내장 변수)
for arg in $@; do
	echo "$arg"
done









