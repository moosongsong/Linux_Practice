#!/bin/bash

# 사용방법: while 표현식
# while true					# while (1)
# do							# {
# 	echo "hello, world"		# 	printf("hello, world\n");
# done						# }

# while true; do				# while (1) {
# 	echo "hello, world"		# 	printf("hello, world\n");
# done						# }

# cnt=1
# while [ "$cnt" -le 5 ]; do		# while (cnt <= 5) {
# 	echo "$cnt: hello, world"	#   printf("%d: hello, world\n", cnt);
# 	((++cnt))					#   ++cnt;
# done							# }
	
# cnt=1
# while ((cnt <= 5)); do
# 	echo "$cnt: hello, world"
# 	((++cnt))				
# done					


# 연습 문제: 사용자로부터 1이상의 양의 정수를 입력 받고 1부터 입력된 값까지의
# 자연수의 총합을 구하는 스크립트를 작성해 보세요 :D
# 단, 잘못된 값을 입력하면 에러 메시지를 출력하고 종료합니다.

# read -p "input: "
# if [[ ! "$REPLY" =~ ^[123456789][[:digit:]]*$ ]]; then
# 	echo "wrong input"
# fi
# 
# sum=0
# cnt=1
# while ((cnt <= REPLY)); do
# 	((sum += cnt))
# 	((++cnt))
# done
# 
# echo "1 to $REPLY: $sum"



# 1부터 100까지의 자연수 중 짝수만 저장하는 스크립트를 구현해 봅니다.

cnt=0
sum=0

while true; do
	((++cnt))
	if ((cnt > 100)); then
		break
	fi

	if (( (cnt % 2) != 0 )); then
		continue
	else
		((sum += cnt))
	fi
done

echo "$sum"



# while: 표현식이 참인 경우, 루프 실행
# until: 표현식이 거짓인 경우, 루프 실행
# 사용 방법:
# until 표현식; to
# ...
# done

cnt=1
sum=0
until ((cnt > 100)); do
	((sum += cnt))
	((++cnt))
done

echo $sum






































