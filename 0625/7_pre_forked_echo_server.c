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

#define MAX_POOL		(3)
void start_child(int ssock, int id) {
	printf("[server %d] running...\n", id);

	while (1) {
		struct sockaddr_in caddr = {0,};
		int caddr_len = sizeof(caddr);
		int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
		if (csock < 0)
			err_quit("accept");

		printf("[server %d] %s is connected...\n", id, inet_ntoa(caddr.sin_addr));

		char buf[BUFSIZ];
		int nRead = read(csock, buf, sizeof(buf));
		if (nRead < 0) {
			err_quit("read");
		}
		else if (nRead == 0) {
			exit(1);
		}
		else {
			write(csock, buf, nRead);
		}
		close(csock);
	}
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

	for (int i = 0; i < MAX_POOL; i++) {
		pid_t pid = fork();
		if (pid < 0) 
			err_quit("fork");
		else if (pid == 0)
			start_child(ssock, i);
		else
			;
	}

	while (wait(NULL) != -1);

	close(ssock);
	return 0;
}

