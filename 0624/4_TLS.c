
// 어떤 함수의 호출 횟수를 계산하고 싶다고 가정합니다.
#if 0
#include <stdio.h>

int foo() {
	int cnt = 0;
	++cnt;
	return cnt;
}

int main() {
	foo();
	foo();
	int cnt = foo();
	printf("%d\n", cnt);
	return 0;
}
#endif

#if 0
// 쓰레드에 안전한 함수(thread-safety)
// -> 호출자의 스택을 사용하는 방법
void foo_r(int *cnt) {	// _r == reentrance(재진입 가능 함수)
	++(*cnt);
}

void* thread_main(void *arg) {
	int cnt = 0;
	foo_r(&cnt);
	foo_r(&cnt);
	foo_r(&cnt);
	printf("%d\n", cnt);
	return NULL;
}

int main() {
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thread_main, NULL);
	pthread_create(&tid2, NULL, thread_main, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
#endif


#if 0
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_key_t idx;	// key??
void destuctor(void *arg) {
	printf("destuctor()\n");
	free(arg);
}


int foo() {
	int *pInt = pthread_getspecific(idx);	// int *pInt = TLS[idx];
	if (pInt == NULL) {
		pInt = malloc(sizeof(int));
		*pInt = 0;
		pthread_setspecific(idx, pInt);			// TLS[idx] = pInt;
	}
	return ++(*pInt);
}

void *thread_main(void *arg) {
	foo();
	foo();
	int cnt = foo();
	printf("%ld: %d\n", pthread_self(), cnt);	// pthread_self() == getpid();
}

int main() {
	// TLS: 원소가 void*인 포인터 배열 ex) void *TLS[128];
	pthread_key_create(&idx, destuctor);	// 비어 있는 가장 작은 인덱스를 발급
																				// 해당 포인터의 자원 해제를 위한 함수를 등록

	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread_main, NULL);
	pthread_create(&t2, NULL, thread_main, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_key_delete(idx);	// destuctor(); -> free(TLS[idx]);
	return 0;
}
#endif


#if 1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

__thread int cnt = 0;	// 정적 TLS
int foo() {
	return ++cnt;
}

void *thread_main(void *arg) {
	foo();
	foo();
	int cnt = foo();
	printf("%ld: %d\n", pthread_self(), cnt);	// pthread_self() == getpid();
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread_main, NULL);
	pthread_create(&t2, NULL, thread_main, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
#endif
