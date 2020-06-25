#include <stdio.h>
#include <pthread.h>

// 서로 다른 쓰레드에 대하여 공유 자원을 사용할 경우,
// 그 자원은 최적화를 수행하지 말자!

void *thread_main(void *arg) {
	volatile int *pFlag = (volatile int *)arg;
	while (*pFlag)	// while (1)
		;
	printf("exit thread_main\n");
	return NULL;
}

int main() {
	int flag = 1;

	pthread_t tid;
	pthread_create(&tid, NULL, thread_main, &flag);

	getchar();
	flag = 0;

	pthread_join(tid, NULL);
	printf("exit main\n");
	return 0;
}
