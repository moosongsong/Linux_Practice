// 5_offset.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	};
	--argc, ++argv;

	int fd1 = open(*argv, O_RDONLY);
	if (fd1 < 0) {
		perror("open");
		return -1;
	}

	int fd2 = open(*argv, O_RDONLY);
	if (fd2 < 0) {
		perror("open");
		return -1;
	}

	char buf1[32] = {0,};
	char buf2[32] = {0,};

	read(fd1, buf1, 5);
	read(fd2, buf2, 5);

	printf("%s\n", buf1);
	printf("%s\n", buf2);

	close(fd1);
	close(fd2);
	return 0;
}
