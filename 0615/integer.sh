#!/bin/bash

# 아래의 두 변수는 모두 문자열을 저장하는 코드입니다.
n1=10
n2=20

# expr에 대하여 피연산자로 변수가 올 수 있습니다.
# expr $n1 + $n2
# expr n1 + n2	# error
# expr ++$n1	# n1+=1, 단점은 단항 연산자에 대해서 동작하지 않습니다.

# echo $[$n1 + $n2]
# echo $[n1 + n2]	# OK, 변수 참조 시 달러를 생략할 수 있습니다.

# age=0	# 0이라는 문자가 저장된 것을 의미
# echo $[age = age + 1]
# echo $[age += 1]
# echo $[++age]

age=0
echo $((age = age + 1))
echo $((age += 1))
echo $((++age))

















