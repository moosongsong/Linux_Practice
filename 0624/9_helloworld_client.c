
// 8_daytime_client.c
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s IPADDRESS\n", *argv);
		return -1;
	}

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("socket");
		return -1;
	}
	--argc, ++argv;

	struct sockaddr_in addr = {0,};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr(*argv);

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("connect");
		return -1;
	}
	
	char buf[BUFSIZ];
	int nRead = read(sock, buf, sizeof(buf));
	if (nRead < 0) {
		perror("read");
		return -1;
	}
	else if (nRead == 0) {	// EOF == 상대방이 연결을 끊었다는 의미
		printf("disconnected...\n");
		close(sock);
		return -1;
	}

	buf[nRead] = '\0';
	printf("%s\n", buf);

	// 소켓 사용이 끝난 경우, 반드시 해제해야 합니다.
	close(sock);
	return 0;
}













