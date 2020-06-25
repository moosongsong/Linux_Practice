#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

// 멀티 프로세스 기반의 서버는 안정적이지만 메모리 사용량이 많고 프로세스 간 
// 데이터 공유도 어렵다는 단점이 있습니다. 이를 해결하기 위해 멀티 쓰레드를
// 도입해 보세요 :D

void __quit(const char *msg, int line) {
	char buf[BUFSIZ];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(1);
}
#define err_quit(msg)	__quit(msg, __LINE__)

void *thread_main(void *arg) {
	int csock = (int)arg;

	char buf[BUFSIZ];
	int nRead = read(csock, buf, sizeof(buf));
	if (nRead < 0) {
		perror("read");
		close(csock);
		return NULL;
	}
	else if (nRead == 0) {
		close(csock);
		return NULL;
	}

	write(csock, buf, nRead);
	close(csock);

	return NULL;
}

int main() {
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1)
		err_quit("socket");

	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
																					

	int value = 1;
	if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1)
		err_quit("setsockopt");
	
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
		err_quit("bind");

	if (listen(ssock, 10) == -1)
		err_quit("listen");
	printf("[server] running...\n");

	while (1) {
		struct sockaddr_in caddr = {0,};
		int caddr_len = sizeof(caddr);
		int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
		if (csock < 0)
			err_quit("accept");
		printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

		pthread_t tid;
		int ret = pthread_create(&tid, NULL, thread_main, (void*)csock);
		if (ret != 0)
			err_quit(strerror(ret));

		ret = pthread_detach(tid);
		if (ret != 0)
			err_quit(strerror(ret));
	}

	close(ssock);
	return 0;
}

