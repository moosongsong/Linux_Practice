// Echo Server
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

// 이전 에코 서버는 에코를 수행한 후, 바로 종료된다는 문제가 있습니다.
// 다른 클라이언트의 접속을 처리할 수 있도록 코드를 변경해 보세요 :D

int main() {
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return -1;
	}

	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	// 서버 소켓이 주소와 바인딩하기 전에 설정
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
		if (csock == -1) {
			perror("accept");
			return -1;
		}
		printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

		char buf[BUFSIZ];
		int nRead = read(csock, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			printf("[server] %s is disconnected...\n", inet_ntoa(caddr.sin_addr));
			close(csock);
			return -1;
		}
		else {
			write(csock, buf, nRead);
		}

		close(csock);
	}
	close(ssock);
	return 0;
}

