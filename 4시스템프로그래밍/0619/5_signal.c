// 5_signal.c

#if 0
// 알람 시그널: 알람 함수에 의해 발생되는 시그널
// 알람 함수에 시간(초)를 전달하고 지정된 시간이 지나면 알람 함수를 수행한 프로세스에게
// SIGALRM을 보냄
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void sigHandler(int signo) {
	printf("SIGALRM!\n");
	alarm(1);
}

int main() {
	if (signal(SIGALRM, sigHandler) == SIG_ERR) {	// == trap sigHandler SIGALRM
		perror("signal");														// trap sigHandler SIGINT
		return -1;
	}

	alarm(10);
	while (1) ;
	return 0;
}
#endif

#if 0
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// 프로세스는 하나 이상의 시그널을 등록할 수 있음
void SIGALRM_Handler(int signo) {
	printf("SIGALRM!\n");
	alarm(1);
}

void SIGINT_Handler(int signo) {
	printf("SIGINT");
}

int main() {
	if (signal(SIGALRM, SIGALRM_Handler) == SIG_ERR) {
		perror("signal");													
		return -1;
	}

	if (signal(SIGINT, SIGINT_Handler) == SIG_ERR) {
		perror("signal");													
		return -1;
	}

	alarm(1);

	while (1) ;
	return 0;
}
#endif

#if 0
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// 핸들러의 인자로는 발생된 시그널의 번호가 전달됩니다.
void sigHandler(int signo) {
	switch (signo) {
		case SIGALRM:
			printf("SIGALRM!\n"); 
			alarm(1);
			break;
		case SIGINT:
			printf("SIGINT");
			break;
	}
}

int main() {
	if (signal(SIGALRM, sigHandler) == SIG_ERR) {
		perror("signal");													
		return -1;
	}

	if (signal(SIGINT, sigHandler) == SIG_ERR) {
		perror("signal");													
		return -1;
	}

	alarm(1);

	while (1) ;
	return 0;
}
#endif

#if 0
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// 시그널을 무시한다는 것은 핸들러 안에서 아무것도 하지 않는 것을 의미하는게 
// 아님, 핸들러가 아무런 일을 하지 않는다 하더라도 일단 핸들러가 호출되었다는 것은
// 처리를 한 것이나 다름 없음
// 시그널을 무시하려면 SIG_IGN(IGN: ignore)
void sigHandler(int signo) {
}

int main() {
// 	if (signal(SIGINT, sigHandler) == SIG_ERR) {
	if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
		perror("signal");													
		return -1;
	}

	while (1)
		;
	return 0;
}
#endif

#if 0
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
// 시그널 복원(해제)
void sigHandler(int signo) {
	printf("SIGINT\n");

	if (signal(SIGINT, SIG_DFL) == SIG_ERR)	// == trap -- SIGINT
		perror("signal");
}

int main() {
 	if (signal(SIGINT, sigHandler) == SIG_ERR) {
		perror("signal");													
		return -1;
	}

	while (1)
		;
	return 0;
}
#endif

#if 1
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

	// 차단할 시그널 목록을 확인
	showMask();
	getchar();


	// 이전 시그널로 복원하고 싶은 경우 
	if (sigprocmask(SIG_SETMASK, &oldMask, NULL) == -1) {
		perror("sigprocmask");
		return -1;
	}
	showMask();

	return 0;
}
#endif
