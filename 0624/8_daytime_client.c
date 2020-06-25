
// 8_daytime_client.c
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

// $ ./a.out 192.168.0.1
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s IPADDRESS\n", *argv);
		return -1;
	}

	// 1. 전화기를 준비
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("socket");
		return -1;
	}
	--argc, ++argv;

	// 2. 전화할 상대방의 전화번호를 설정
	// IP Address
	struct sockaddr_in addr = {0,};
	addr.sin_family = AF_INET;	// IPv4 주소 체계 사용
	addr.sin_port = htons(13);	// port for daytime server
	addr.sin_addr.s_addr = inet_addr(*argv); 	// 192.168.0.1 -> 32bit number

	// 3. 통화 버튼 누르기
	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("connect");
		return -1;
	}
	
	// 서버와 연결이 확립되면 서버는 클라이언트에게 현재 시간을 문자열 형태로 
	// 전송하고 연결을 끊습니다.
	char buf[BUFSIZ];
	int nRead = read(sock, buf, sizeof(buf));
	if (nRead < 0) {
		perror("read");
		return -1;
	}
	else if (nRead == 0) {	// EOF == 상대방이 연결을 끊었다는 의미
		// ...	
	}

	buf[nRead] = '\0';
	printf("%s\n", buf);

	// 소켓 사용이 끝난 경우, 반드시 해제해야 합니다.
	close(sock);
	return 0;
}













