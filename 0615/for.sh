#!/bin/bash

# for: list-based loop
# 사용 방법
# for 변수명 in 리스트
# do
#   ...
# done

# for var in 0 1 2 3 4 5 6 7 8 9 
# do
# 	echo "$var: hello, world"
# done

# for var in {0..9}; do
# 	echo "$var: hello, world"
# done

# for fname in *; do
# 	echo "file name: $fname"
# done

# 사용자로부터 1이상의 자연수를 입력 받아 1부터 입력된 값까지의 자연수의 총합
# 구해보세요. 단! while이 아닌 for를 사용해 보세요 :D
# read -p "input: "
# 
# sum=0
# # for num in {1..$REPLY}; do --> ERROR, 중괄호 확장에는 상수만 사용 가능합니다. ㅠ^ㅠ
# for num in $(seq $REPLY); do
# 	((sum += num))
# done
# 
# echo $sum

# for i in "hello" "world"; do
# 	echo $i
# done

# 비교적 최근에 C언어와 유사한 형태의 for loop를 제공합니다.
# usage: for (( expr1; expr2; expr3 )); do
# ...
# done

# for i in {0..4}; do
# 	echo "$i: hello, world"
# done
# 
# for ((i = 0; i < 5; i++)); do
# 	echo "$i: hello, world"
# done


# 반복문도 중첩이 가능합니다.
# for ((i = 2; i < 10; ++i)); do
# 	for ((j = 1; j < 10; j++)); do
# 		printf "%d x %d = %d\n" $i $j $((i * j))
# 	done
# 	echo	# 개행
# done

# 연습 문제: 아래와 같은 달력을 출력해 보세요  :D
# Su Mo Tu We Th Fr Sa
#  1  2  3  4  5  6  7
#  8  9 10 11 12 13 ..
#  ...................
# 31

# printf("%3d", 10); == printf "%3d" 10
echo " Su Mo Tu We Th Fr Sa"

for day in {1..31}; do
	printf "%3d" $day
	(( (day % 7) == 0 )) && echo
done
echo







































































