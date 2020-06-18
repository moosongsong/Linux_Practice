// 9_unlink.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// ls -l hello.txt -> 연결 계수: 1
// 프로세스가 생성되지 않았으므로 참조 계수는 존재하지 않음
int main() {
	int fd = open("hello.txt", O_RDONLY);	// 연결 계수: 1, 참조 계수: 1
	if (fd < 0) {												
		perror("open");
		return -1;
	}

	// 파일 삭제: unlink
	if (unlink("hello.txt") < 0) {	// 연결 계수: 0, 참조 계수: 1
		perror("unlink");
		return -1;
	}
	getchar();	// 만약 참조 계수가 1 이상인 상황에서 연결 계수가 0인 경우
							// 해당 파일은 더이상 파일시스템에서 보이지 않습니다.

	char buf[BUFSIZ];
	while (1) {
		ssize_t nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		else {
			write(1, buf, nRead);
		}
	}

	close(fd);	// 연결 계수: 0, 참조 계수: 0  --> 파일 시스템에서 삭제됩니다.
	return 0;
}


