// 5_syscall.c

#if 0
#include <stdio.h>

// 표준 입력으로부터 받은 데이터를 표준 출력으로 전송하는 프로그램을 구현합니다.
int main(int argc, char **argv) {
	char buf[4096];
	while (1) {
		if (fgets(buf, sizeof(buf), stdin)) {
			fputs(buf, stdout);
		}
		else {	// NULL
			if (ferror(stdin)) {
				perror("fgets");
				return -1;
			}
			else if (feof(stdin)) {
				break;
			}
		}
	}
	return 0;
}
#endif

#if 1
#include <unistd.h>
#include <stdio.h>

// 아래의 코드를 시스템콜을 사용한 코드로 변경해 봅니다.
int main(int argc, char **argv) {
	char buf[4096];
	while (1) {
		ssize_t nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {	// EOF
			break;
		}
		else {
			ssize_t nWritten = write(1, buf, nRead);
			if (nWritten < 0) {
				perror("write");
				return -1;
			}
			else if (nWritten != nRead) {
				fprintf(stderr, "write error: nWritten / nRead\n");
				return -1;
			}
		}
	}
	return 0;
}
#endif
