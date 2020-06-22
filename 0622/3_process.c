
#if 0
// 3_process.c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid = getpid();
	printf("pid = %d\n", pid);

	return 0;
}
#endif

#if 1
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	// fork를 호출한 곳에는 자식 프로세스의 아이디가 반환되고
	// fork에 의해 생성된 곳에서는 0이 반환됨
	pid_t pid = fork();
	if (pid > 0) {
		printf("[parent] hello, world\n");
	}
	else if (pid == 0) {
		printf("[child] hello, world\n");
	}
	else {
		perror("fork");
		return -1;
	}

	return 0;
}
#endif










