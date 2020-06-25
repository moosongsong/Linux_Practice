// Echo Server
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
// 아래의 코드를 넌블럭 코드로 변경해 보세요 :D

int fd_table[1024];
int cnt = 0;

int main() {
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return -1;
	}

	if (fcntl(ssock, F_SETFL, O_NONBLOCK) == -1) {
		perror("fcntl");
		return -1;
	}
	

	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	int value = 1;
	if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1) {
		perror("setsockopt");
		return -1;
	}
	
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
		perror("bind");
		return -1;
	}

	if (listen(ssock, 10) == -1) {
		perror("listen");
		return -1;
	}
	printf("[server] running...\n");

	while (1) {
		struct sockaddr_in caddr = {0,};
		int caddr_len = sizeof(caddr);
		int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
		if (csock < 0) {
			if (errno != EAGAIN) {
				perror("accept");
				return -1;
			}
		}

		if (csock > 0) {
			printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));
			if (fcntl(csock, F_SETFL, O_NONBLOCK) == -1) {
				perror("fcntl");
				return -1;
			}
			fd_table[cnt++] = csock;
		}

		char buf[BUFSIZ];
		for (int i = 0; i < cnt; i++) {
			int nRead = read(fd_table[i], buf, sizeof(buf));
			if (nRead < 0) {
				if (errno != EAGAIN) {
					perror("read");
					return -1;
				}
			}
			else if (nRead == 0) {
				close(fd_table[i]);
				fd_table[i] = fd_table[--cnt];
				return -1;
			}
			else {
				write(fd_table[i], buf, nRead);
				close(fd_table[i]);
				fd_table[i] = fd_table[--cnt];
			}
		}
	}

	close(ssock);
	return 0;
}

