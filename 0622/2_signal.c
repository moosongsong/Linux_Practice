// 5_signal.c

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sigHandler(int signo) {
	if (signo == SIGINT) {
		printf("cought SIGINT!\n");
		if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
			perror("signal");
			exit(1);
		}
	}
}

int main() {
	// SIGINT에 대한 핸들러를 등록
	if (signal(SIGINT, sigHandler) == SIG_ERR) {
		perror("signal");
		return -1;
	}

	// 시그널 마스크 데이터 생성 및 초기화
	sigset_t newMask;
 	if (sigemptyset(&newMask) == -1) {
		perror("sigemptyset");
		return -1;
	}

	// 차단할 시그널을 설정
	if (sigaddset(&newMask, SIGINT) == -1) {
		perror("sigaddset");
		return -1;
	}

	// 차단할 시그널을 등록
	sigset_t oldMask;
	if (sigprocmask(SIG_BLOCK, &newMask, &oldMask) == -1) {
		perror("sigprocmask");
		return -1;
	}

	printf("press CTRL + C\n");
	sleep(10);

	// 블록된 시그널이 있는지 확인
	sigset_t pendingMask;
	if (sigpending(&pendingMask) == -1) {
		perror("sigpending");
		return -1;
	}

	int ret = sigismember(&pendingMask, SIGINT);
	if (ret == -1) {
		perror("sigismember");
		return -1;
	}
	else if (ret == 1) {
		printf("\nSIGINT is pending...\n");
	}

	// 기존 시그널로 복원
	if (sigprocmask(SIG_SETMASK, &oldMask, NULL) == -1) {
		perror("sigprocmask");
		return -1;
	}

	printf("SIGINT unblocked\n");
	printf("press CTRL + C\n");
	sleep(10);

	return 0;
}
