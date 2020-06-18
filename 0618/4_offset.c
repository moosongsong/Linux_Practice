// 4_offset.c
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

long getFileSize(int fd) {
	if (fd < 0) {
		fprintf(stderr, "getFileSize: fd is wrong\n");
		return -1;
	}

	off_t oldPos = lseek(fd, 0, SEEK_CUR);
	if (oldPos == -1) {
		perror("lseek");
		return -1;
	}

	off_t fsize = lseek(fd, 0, SEEK_END);
	if (fsize == -1) {
		perror("fseek");
		return -1;
	}

	if (lseek(fd, oldPos, SEEK_SET) == -1) {
		perror("lseek");
		exit(-1);
	}
	return fsize;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	}
	--argc, ++argv;

	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	long fsize = getFileSize(fd);
	printf("%ld\n", fsize);

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

	close(fd);
	return 0;
}
