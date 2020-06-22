#if 0
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sigHandler(int signo) {
	if (signo == SIGCHLD) {
		int exit_code;
		wait(&exit_code);
		printf("status: %d\n", WEXITSTATUS(exit_code));
	}
}

int main() {
	// 자식의 종료 코드를 읽어오기 위해 핸들러를 설치
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		return -1;
	}

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
		return 10;
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
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sigHandler(int signo) {
	if (signo == SIGCHLD) {
		int exit_code;
		wait(&exit_code);
		printf("status: %d\n", WEXITSTATUS(exit_code));
	}
}

int main() {
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		return -1;
	}

	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			perror("fork");
			return -1;
		}
		else if (pid == 0) {
			printf("\t\tcreated child: %d\n", i + 1);
			sleep(5);
			return i + 1;
		}
	}

	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	return 0;
}
#endif

#if  0
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sigHandler(int signo) {
	if (signo == SIGCHLD) {
		int exit_code;

		while (wait(&exit_code) > 0)
			printf("status: %d\n", WEXITSTATUS(exit_code));
	}
}

int main() {
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		return -1;
	}

	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			perror("fork");
			return -1;
		}
		else if (pid == 0) {
			printf("\t\tcreated child: %d\n", i + 1);
			sleep(5);
			return i + 1;
		}
	}

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
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sigHandler(int signo) {
	if (signo == SIGCHLD) {
		int exit_code;

		// waitpid
		while (wait(&exit_code) > 0)
			printf("status: %d\n", WEXITSTATUS(exit_code));
	}
}

int main() {
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		return -1;
	}

	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			perror("fork");
			return -1;
		}
		else if (pid == 0) {
			printf("\t\tcreated child: %d\n", i + 1);
			sleep(i + 1);
			return i + 1;
		}
	}

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
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void sigHandler(int signo) {
	if (signo == SIGCHLD) {
		int exit_code;

		// while (wait(&exit_code) > 0)
		while (waitpid(-1, &exit_code, WNOHANG) > 0)
			printf("status: %d\n", WEXITSTATUS(exit_code));
	}
}

int main() {
	if (signal(SIGCHLD, sigHandler) == SIG_ERR) {
		perror("signal");
		return -1;
	}

	for (int i = 0; i < 10; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			perror("fork");
			return -1;
		}
		else if (pid == 0) {
			printf("\t\tcreated child: %d\n", i + 1);
			sleep(i + 1);
			return i + 1;
		}
	}

	while (1) {
		sleep(1);
		printf("[parent] .\n");
	}

	return 0;
}
#endif
