#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		pthread_mutex_lock(&mtx);	// spin_lock(&lock);
		//----------------------
		++cnt;	
		sleep(60);
		//----------------------
		pthread_mutex_unlock(&mtx);	// spin_unlock(&lock);
	}
	return NULL;
}

int main() {
	pthread_t tid[2];
	for (int i = 0; i < 2; i++)
		pthread_create(&tid[i], NULL, thread_main, NULL);

	for (int i = 0; i < 2; i++)
		pthread_join(tid[i], NULL);

	printf("%d\n", cnt);
	return 0;
}


