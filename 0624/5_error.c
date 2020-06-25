
#if 0
#include <stdio.h>

int main() {
	FILE *fp = fopen("xxx", "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}
	
	char buf[BUFSIZ];
	fgets(buf, sizeof(buf), fp);

	fclose(fp);
	return 0;
}
#endif


#include <stdio.h>
#include <string.h>
#include <pthread.h>

int main() {
	pthread_t tid;

	// ...
// 	if (pthread_join(tid, NULL) != 0) {
// 		perror("pthread_join");
// 		return -1;
// 	}

	int ret = pthread_join(tid, NULL);
	if (ret) {
// 		fprintf(stderr, "pthread_join: %d\n", ret);
		fprintf(stderr, "pthread_join: %s\n", strerror(ret));
		return -1;
	}

	return 0;
}

















