// 5_signal.c

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// 시그널 펜딩(보류)
// 1. 차단과 해제
void showMask() {
	sigset_t curMask;
	if (sigprocmask(0, NULL, &curMask) == -1) {
		perror("sigprocmask");
		return;
	}

	printf("blocked signal list: ");
	if (sigismember(&curMask, SIGINT)) printf("SIGINT ");
	if (sigismember(&curMask, SIGQUIT)) printf("SIGQUIT ");
	if (sigismember(&curMask, SIGALRM)) printf("SIGALRM ");
	printf("\n");
}

int main() {
	// 시그널 마스크 데이터 생성 및 초기화
	sigset_t newMask;
// 	if (sigemptyset(&newMask) == -1) {
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

	// 차단할 시그널 목록을 확인
	showMask();
	getchar();


	// 이전 시그널로 복원하고 싶은 경우 
// 	if (sigprocmask(SIG_SETMASK, &oldMask, NULL) == -1) {
		perror("sigprocmask");
		return -1;
	}
	showMask();

	return 0;
}
