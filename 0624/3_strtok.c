
#if 0
#include <stdio.h>
#include <string.h>

int main() {
	char hp[] = "010-1234-5678";
	char *p = strtok(hp, "-");
	while (p) {
		printf("[%s]\n", p);
		p = strtok(NULL, "-");
	}
	return 0;
}
#endif

#if 1
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *thread_main1(void *arg) {
	char str[] = "010-1234-5678";
	// char *p = strtok(str, "-");
	char *savePtr;
	char *p = strtok_r(str, "-", &savePtr);
	while (p) {
		printf("[%s]\n", p);
		p = strtok_r(NULL, "-", &savePtr);
	}
	return NULL;
}

void *thread_main2(void *arg) {
	char str[] = "192.168.0.1";
	// char *p = strtok(str, ".");
	char *savePtr;
	char *p = strtok_r(str, ".", &savePtr);
	while (p) {
		printf("[%s]\n", p);
		p = strtok_r(NULL, ".", &savePtr);
	}
	return NULL;
}

int main() {
	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread_main1, NULL);
	pthread_create(&t2, NULL, thread_main2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
#endif
