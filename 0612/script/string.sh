#!/bin/bash

# str="hello"
# echo $(expr length $str)
# echo ${#str}

#    12345  <--- index
# str="hello"
# echo $(expr index $str 'h')		# 1
# echo $(expr index $str 'l')		# 3, 일치하는 첫 번째 문자의 인덱스를 반환
# echo $(expr index $str 'el')		# 2, 일치하는 첫 번째 문자의 인덱스를 반환

# str="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# echo $(expr substr $str 1 4)	# ABCD, expr의 경우 문자열의 시작은 1
# echo ${str:0:4}					# ABCD, ${}의 경우 문자열의 시작은 0
# echo ${str:23}					# XYZ, 길이를 명시하지 않으면 문자열의 끝까지 추출


# str="abcABC123ABCabc"
#    |----|
#    |----------|

# echo ${str#a*C}		# 123ABCabc
# echo ${str##a*C}	# abc

# 연습문제 1. 아래의 문자열에서 파일명만 추출해 보세요 :D
# path="/home/linux/script/a.sh"
# echo ${path##*/}	# basename

# str="abcABC123ABCabc"
#                 ||
#     |------------|

# echo ${str%b*c}		# abcABC123ABCa
# echo ${str%%b*c}	# a

# 연습문제 2. 디렉터리 부분만 추출해 보세요 :D
# path="/home/linux/script/a.sh"
#                       |---|
#     |---------------------|
# echo ${path%/*}


str="abcABC123ABCabc"

# 처음 일치하는 abc를 ---로 치환
# echo ${str/abc/---}		# ---ABC123ABCabc

# 일치하는 모든 abc를 ---로 치환
# echo ${str//abc/---}	# ---ABC123ABC---

# 앞에서 일치하는 abc를 ---로 치환
# echo ${str/#abc/---}	# ---ABC123ABCabc

# 뒤에서 일치하는 abc를 ---로 치환
# echo ${str/%abc/---}	# abcABC123ABC---

# 연습 문제 3. 경로를 한 줄씩 출력해 보세요 :D
# PATH: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

echo -e ${PATH//:/"\n"}


































