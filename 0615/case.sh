#!/bin/bash

# 3가지 메뉴 시스템을 생각해 봅시다.
clear

# echo "
# 1. 짜장면
# 2. 짬뽕
# 3. 턍슉
# 0. 종료"
# 
# read -p "*메뉴를 선택해 주세요: "
# 
# # usage: case 변수명 in
# case $REPLY in								# switch (REPLY) {
# 	0) exit 0								#   case 0: exit(0);
# 		;;									#     break
# 	1) echo "짜장면을 선택하셨습니다.";;	#   case 1: printf("...\n"); break;
# 	2) echo "짬뽕을 선택하셨습니다.";;		#   case 2: printf("...\n"); break;
# 	3) echo "탕슉을 선택하셨습니다.";;		#   case 3: printf("...\n"); break;
# 	*) echo "잘못입력하셨습니다."			# 	default:
# 		exit;;								#     ...
# esac										# }

echo "
a. 짜장면
b. 짬뽕
c. 턍슉
q. 종료"

read -p "*메뉴를 선택해 주세요: "

case $REPLY in								
	q|Q) exit 0;;								
	a|A) echo "짜장면을 선택하셨습니다.";;
	b|B) echo "짬뽕을 선택하셨습니다.";;	
	c|C) echo "탕슉을 선택하셨습니다.";;
	*) echo "잘못입력하셨습니다."
	   exit;;					
esac						


