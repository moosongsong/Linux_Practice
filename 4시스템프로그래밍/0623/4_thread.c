
#if 0
#include <stdio.h>
#include <unistd.h>

void print(const char *str) {
	for (int i = 0; i < 10; i++) {
		printf("%s\n", str);
		sleep(1);
	}
}

int main() {
	print("\t\tdo something...");
	while (1) {
		printf(".\n");
		sleep(1);
	}

	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
// 이전의 프로그램은 코드가 직렬적으로 수행되었습니다.
// 이제 병행적으로 수행되도록 멀티 쓰레드를 도입합니다.

// void print(const char *str) {
void *print(void *arg) {
	const char *str = (const char *)arg;
	for (int i = 0; i < 10; i++) {
		printf("%s\n", str);
		sleep(1);
	}
}

int main() {
	// print("\t\tdo something...");

	// 쓰레드 생성(POSIX Thread)
	pthread_t tid;
	pthread_create(&tid, NULL, print, "\t\tdo something...");

	while (1) {
		printf(".\n");
		sleep(1);
	}

	return 0;
}
#endif

#if 1
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// 자바와 같은 managed language는 메인 쓰레드가 종료된다 하더라도
// 워커 쓰레드가 구동중이면 프로세스는 종료되지 않습니다.
// 그러나 pthread는 메인 쓰레드가 종료되면 이는 곧 프로세스의 종료이므로
// 워커 쓰레드가 존재한다 하더라도 프로세스는 종료됩니다.
void *print(void *arg) {
	const char *str = (const char *)arg;
	for (int i = 0; i < 10; i++) {
		printf("%s\n", str);
		sleep(1);
	}
}

int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, print, "\t\tdo something...");	// fork();

	// 만약 워커 쓰레드가 종료될 때까지 대기하려면 pthread_join 함수를 사용하면 됩니다.
	pthread_join(tid, NULL);																	// wait();
	return 0;
}
#endif
