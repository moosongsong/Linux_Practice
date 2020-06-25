
#if 0
#include <stdio.h>
// 어떤 함수의 호출 횟수를 계산하고 싶다고 가정합니다.
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
#include <stdio.h>
int cnt = 0;	// global is evil! 앙마
void foo() {
	++cnt;
}

int main() {
	foo();
	foo();
	foo();
	printf("%d\n", cnt);
	return 0;
}
#endif

#if 0
#include <stdio.h>
int foo() {
	static int cnt = 0;
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
#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int foo() {
	static int cnt = 0;
	pthread_mutex_lock(&mtx);
	// -----------------------
	++cnt;
	// -----------------------
	pthread_mutex_unlock(&mtx);
	return cnt;
}

void* thread_main(void *arg) {
	foo();
	foo();
	int cnt = foo();
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

#if 1
#include <stdio.h>
#include <pthread.h>

// 아래의 함수는 쓰레드에 안전하지 않음
int foo() {
	static int cnt = 0;
	++cnt;
	return cnt;
}

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
