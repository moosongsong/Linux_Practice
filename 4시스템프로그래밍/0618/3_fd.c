
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	--argc, ++argv;

	int fd1 = open(argv[0], O_RDONLY);
	if (fd1 < 0) {
		perror("open");
		return -1;
	}
	printf("fd: %d\n", fd1);	// 3

	int fd2 = open(argv[1], O_RDONLY);
	if (fd2 < 0) {
		perror("open");
		return -1;
	}
	printf("fd: %d\n", fd2);	// 4

	close(fd1);
	close(fd2);
	return 0;
}

