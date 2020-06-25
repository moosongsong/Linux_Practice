#if 0
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

// 프로세스가 생성될 때, 메모리를 복제하여 생성!
int global = 0;
int main() {
	if (fork() == 0) {
		++global;	// COW(Copy On Write)
		printf("[child] global = %d\n", global);
		return 0;
	}

	wait(NULL);
	printf("[parent] global = %d\n", global);
	return 0;
}
#endif

#if 1
#include <stdio.h>
#include <pthread.h>
// 프로세스와 다르게 쓰레드는 프로세스의 모든 메모리를 공유한다고 할 수 있다.

// fork() -> do_fork();
// pthread_create -> ... -> do_fork();

// 쓰레드와 프로세스의 같은점: 프로세스와 쓰레드는 같은 개념
//                     차이점: 메모리 공유 유무


int global = 0;
void *thread_main(void *arg) {
	++global;
	printf("[worker thread] global = %d\n", global);
	return NULL;
}

int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, thread_main, NULL);

	pthread_join(tid, NULL);
	printf("[main thread] global = %d\n", global);
	return 0;
}
#endif
