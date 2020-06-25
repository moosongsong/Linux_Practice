
#if 0
// 2_named_pipe.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FIFO\n", *argv);
		return -1;
	}
	--argc, ++argv;

	if (mkfifo(*argv, 0666) == -1) {	// $ mkfifo myfifo
		perror("mkfifo");
		return -1;
	}
	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}
	char buf[BUFSIZ];
	while (1) {
		int nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		write(1, buf, nRead);
	}
	close (fd);
	unlink(*argv);	// 다 사용한 파이프는 삭제합니다.
	return 0;
}

#endif

#if 1
// 2_named_pipe.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FIFO\n", *argv);
		return -1;
	}
	--argc, ++argv;

	int fd = open(*argv, O_WRONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	char buf[BUFSIZ];
	while (1) {
		int nRead = read(0, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		write(fd, buf, nRead);
	}
	close(fd);
	return 0;
}

#endif
