
// Echo Server
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	// 1. 서버용 전화기 생성
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return -1;
	}

	// 2. 전화번호 설정
	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
												//  ^--- "192.168.0.1" -> IPv4
	
	// 3. 전화기에 전화번호 등록
	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
		perror("bind");
		return -1;
	}

	// 4. 동시 접속된 클라이언트를 위한 백로그(큐)를 설정
	if (listen(ssock, 10) == -1) {
		perror("listen");
		return -1;
	}

	printf("[server] running...\n");

	// 5. 클라이언트의 접속을 대기
	//  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	struct sockaddr_in caddr = {0,};	// client address
	int caddr_len = sizeof(caddr);
	int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
	if (csock == -1) {
		perror("accept");
		return -1;
	}
	printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));
	//																					^--- IPv4 -> "192.168.0.1"

	char buf[BUFSIZ];
	int nRead = read(csock, buf, sizeof(buf));	// 클라이언트로부터 전송된 문자열을 읽어옵니다.
	if (nRead < 0) {
		perror("read");
		return -1;
	}
	else if (nRead == 0) {
		printf("[server] %s is disconnected...\n", inet_ntoa(caddr.sin_addr));
		close(csock);
		close(ssock);
		return -1;
	}
	else {
		write(csock, buf, nRead);
	}

	close(csock);
	close(ssock);
	return 0;
}


