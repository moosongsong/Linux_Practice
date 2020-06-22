// 5_child.c
#if 1
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

