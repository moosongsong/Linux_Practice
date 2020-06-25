// 4_nonblock.c
#if 0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	int fifo = open("myfifo", O_RDONLY);	// $ mkfifo myfifo
	if (fifo < 0) {
		perror("open");
		return -1;
	}

	// 키보드로부터 입력 받은 데이터와 파이프로부터 입력 받은 데이터를
	// 출력하는 코드를 구현해 봅니다.
	char buf[BUFSIZ];
	while (1) {
		// keyboard
		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead > 0) {
			buf[nRead-1] = 0;
			printf("keyboard: %s\n", buf);
		}

		// pipe
		nRead = read(fifo, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead > 0) {
			buf[nRead-1] = 0;
			printf("fifo: %s\n", buf);
		}
	}
	return 0;
}
#endif

#if 1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
	int fifo = open("myfifo", O_RDONLY);	// $ mkfifo myfifo
	if (fifo < 0) {
		perror("open");
		return -1;
	}

	// 키보드와 파이프의 속성을 non-block으로 변경합니다.
	if ((fcntl(0, F_SETFL, O_NONBLOCK) == -1) || (fcntl(fifo, F_SETFL, O_NONBLOCK) == -1)) {
		perror("fcntl");
		return -1;
	}

	char buf[BUFSIZ];
	while (1) {
		// keyboard
		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			if (errno != EAGAIN) {
				perror("read");
				return -1;
			}
		}
		else if (nRead > 0) {
			buf[nRead-1] = 0;
			printf("keyboard: %s\n", buf);
		}

		// pipe
		nRead = read(fifo, buf, sizeof(buf));
		if (nRead < 0) {
			if (errno != EAGAIN) {
				perror("read");
				return -1;
			}
		}
		else if (nRead > 0) {
			buf[nRead-1] = 0;
			printf("fifo: %s\n", buf);
		}
	}
	return 0;
}
#endif
