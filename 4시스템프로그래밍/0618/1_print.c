// 1_print.c
// ./a.out hello.txt
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	}
	--argc, ++argv;

	int fd = open(*argv, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	char buf[BUFSIZ];	// BUFSIZ: 효율적인 버퍼의 크기가 정의된 매크로(stdio.h)
	while (1) {
		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		else {
			write(fd, buf, nRead);
		}
	}

	if (close(fd) == -1) {
		perror("close");
		exit(-1);	// or return -1;
	}

	return 0;
}

