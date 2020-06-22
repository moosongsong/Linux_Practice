// 5_child.c
#if 0
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		return -1;
	}
	else if (pid == 0) {	// child process
		for (int i = 0; i < 5; i++) {
			sleep(1);
			printf("[child] do something...\n");
		}
		return 0;
	}

	// parent process
	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}
	return 0;
}
#endif

#if 0
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		return -1;
	}
	else if (pid == 0) {	// child process
		for (int i = 0; i < 5; i++) {
			sleep(1);
			printf("[child] do something...\n");
		}
		return 100;
	}

	int exit_code;
	wait(&exit_code);	// 자식의 종료 코드를 읽어옵니다.
	printf("exit code from child: %d\n", (exit_code >> 8) & 0xFF);
	printf("exit code from child: %d\n", WEXITSTATUS(exit_code));

	// parent process
	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}
	return 0;
}
#endif

#if 0
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		return -1;
	}
	else if (pid == 0) {	// child process
		for (int i = 0; i < 5; i++) {
			sleep(1);
			printf("[child] do something...\n");
		}
		return 100;
	}

	int exit_code;
	wait(&exit_code);	// 자식의 종료 코드를 읽어옵니다.
	printf("exit code from child: %d\n", (exit_code >> 8) & 0xFF);
	printf("exit code from child: %d\n", WEXITSTATUS(exit_code));

	// parent process
	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}
	return 0;
}
#endif

#if 1
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	pid_t pid = fork();
	if (pid < 0) {
		perror("fork");
		return -1;
	}
	else if (pid == 0) {	// child process
		for (int i = 0; i < 5; i++) {
			sleep(1);
			printf("[child] do something...\n");
		}
		// return 100;
		abort();	// 비정상 종료
	}

	int exit_code;
	wait(&exit_code);	// 자식의 종료 코드를 읽어옵니다.

	if ((exit_code & 0xFF) == 0) {	// 정상 종료
		printf("exit_code = %d\n", WEXITSTATUS(exit_code));
	}
	else {	// 비정상 종료
		printf("exit_code = %d\n", WTERMSIG(exit_code));
	}

	// parent process
	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}
	return 0;
}
#endif
