// 6_exit.c
#if 0
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// 워커 쓰레드 종료 방법 1. 시작 함수가 종료
void *thread_main(void *arg) {
	for (int i = 0; i < 5; i++) {
		sleep(1);
		printf("[worker] ...\n");
	}
	// return NULL;

	const char *msg = "hello, world";
	char *p = malloc(strlen(msg) + 1);
	strcpy(p, msg);
	return p;	// 쓰레드 함수 내의 지역 객체의 주소를 반환하면 안됩니다.
						// 반환된 값은 pthread_join 함수의 2번째 인자로 읽어올 수 있습니다.
}

int main() {
	pthread_t t;
	pthread_create(&t, 0, thread_main, 0);

	char* p;
	pthread_join(t, (void**)&p);
	printf("msg from thread: %s\n", p);
	free(p);
	return 0;
}


#endif

#if 1
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// 워커 쓰레드 종료 방법 2. pthread_exit 함수 사용
void foo() {
	const char *msg = "hello, world";
	char *p = malloc(strlen(msg) + 1);
	strcpy(p, msg);
	pthread_exit(p);	// == return p;
}

void *thread_main(void *arg) {
	for (int i = 0; i < 5; i++) {
		sleep(1);
		printf("[worker] ...\n");
	}
	foo();
	return NULL;

}

int main() {
	pthread_t t;
	pthread_create(&t, 0, thread_main, 0);

	char* p;
	pthread_join(t, (void**)&p);
	printf("msg from thread: %s\n", p);
	free(p);
	return 0;
}


#endif
