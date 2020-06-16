#!/bin/bash

#if ...
# ...
#else
# ...
#endif

# void foo() {
# }

# if (flag)
# {
# }

# 사용자로부터 입력 받은 숫자가 0인지 아닌지를 판단하는 코드
read -p "input integer: "

# if test "$REPLY" -eq 0		# if (REPLY == 0)
# then						# {
# 	echo "zero"				# 	printf("zero\n");
# fi							# }
# 
# if test "$REPLY" -ne 0; then	# if (REPLY != 0) {
# 	echo "not zero"				#   printf("not zero\n");
# fi								# }

# if [ "$REPLY" -eq 0 ]
# then				
# 	echo "zero"	
# fi			
# 
# if [ "$REPLY" -ne 0 ]; then	
# 	echo "not zero"			
# fi						


# if [ "$REPLY" -eq 0 ]; then	# if (REPLY == 0) {
#   echo "zero"				#   printf("zero\n");
# else						# } else {
#   echo "not zero"			#   printf("not zero\n");
# fi							# }


# if [ "$REPLY" -eq 0 ]; then		# if (REPLY == 0) {
# 	echo "zero"					# 	printf("zero\n");
# else							# } else {
# 	if [ "$REPLY" -gt 0 ];		# 	if (REPLY > 0) {
# 		echo "positive"			#	  printf("printf\n");
# 	else						#	} else {
# 		echo "negative"			# 	  printf("negative\n");
# 	if							#   }
# fi								# }

# 자동 들여쓰기 동작하지 않는 분들은 ~/.vimrc 파일에 다음의 한 줄을 추가하세요
# filetype indent on

# 들여쓰기를 수정하려면 다음과 같이 단축키를 입력
# 1. 현재 커서를 기준으로 아래의 모든 행에 대하여 들여쓰기를 수행: =G
# 2. 현재 커서를 기준으로 위의 모든 행에 대하여 들여쓰기를 수행: =gg

if [ "$REPLY" -gt 0 ]; then 	# if (REPLY > 0) {
	echo "positive"				#   printf("positive\n");
elif [ "$REPLY" -lt 0 ]; then	# } else if (REPLY < 0) {
	echo "negative"				#   printf("negative\n");
else							# } else { 
	echo "zero"					#   printf("zero\n");
fi								# }































