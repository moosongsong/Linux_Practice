
// 2_mycp.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s FILE1 FILE2\n", *argv);
		return -1;
	}
	--argc, ++argv;

	int srcFile = open(argv[0], O_RDONLY);
	if (srcFile < 0) {
		perror("open");
		return -1;
	}

	int dstFile = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dstFile < 0) {
		perror("open");
		return -1;
	}

	char buf[BUFSIZ];
	while (1) {
		ssize_t nRead = read(srcFile, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		else {
			write(dstFile, buf, nRead);
		}
	}

	close(dstFile);
	close(srcFile);

	return 0;
}







