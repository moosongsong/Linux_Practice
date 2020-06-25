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
#include <signal.h>

void __quit(const char *msg, int line) {
	char buf[BUFSIZ];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(1);
}
#define err_quit(msg)	__quit(msg, __LINE__)

void signal_handler(int signo) {
	if (signo == SIGCHLD) {
		while (waitpid(-1, NULL, WNOHANG) > 0);
	}
}

int main() {
	if (signal(SIGCHLD, signal_handler) == SIG_ERR)
		err_quit("signal");

	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1)
		err_quit("socket");

	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);	// 현재 시스템에 할당된 모든 아이피로부터
																							// 접속을 허용하겠다는 의미

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

		pid_t pid = fork();
		if (pid > 0) {
			close(csock);
		}
		else if (pid == 0) {	
			close(ssock);

			// 자식 프로세스에서 입출력을 수행합니다.
			char buf[BUFSIZ];
			int nRead = read(csock, buf, sizeof(buf));
			if (nRead < 0) {
				err_quit("read");
			}
			else if (nRead == 0) {
				return -1;
			}
			else {
				buf[nRead] = 0;
				write(csock, buf, nRead);
			}
			close(csock);
			return 0;
		}
		else {
			err_quit("fork");
		}
	}

	close(ssock);
	return 0;
}

