
#if 0
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const char *global = "global";	// data area
int main() {
	const char *local = "local";	// stack area
	char **str = malloc(sizeof(char*));	// heap area
	if (str == NULL) {
		perror("malloc");
		return -1;
	}
	*str = "heap";

	pid_t pid = fork();
	if (pid > 0) {
		sleep(3);
		printf("[parent] %s, %s, %s\n", global, local, *str);
	}
	else if (pid == 0) {
		global = "GLOBAL";
		local = "LOCAL";
		*str = "HEAP";
		printf("[child] %s, %s, %s\n", global, local, *str);
	}
	else {
		perror("fork");
		return -1;
	}

	return 0;
}
#endif


#if 0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

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

	pid_t pid = fork();
	if (pid > 0) {
		sleep(3);
		printf("[parent] ");

		char buf[10];
		int nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}

		buf[nRead] = '\0';
		printf("%s\n", buf);
	}
	else if (pid == 0) {
		close(fd);
		return 0;
	}
	else {
		perror("fork");
		return -1;
	}

	close(fd);
	return 0;
}
#endif

#if 1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

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

	pid_t pid = fork();
	if (pid > 0) {
		printf("[parent] ");
		char buf[10];
		int nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		buf[nRead] = '\0';
		printf("%s\n", buf);
	}
	else if (pid == 0) {
		printf("[child] ");
		char buf[10];
		int nRead = read(fd, buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		buf[nRead] = '\0';
		printf("%s\n", buf);
	}
	else {
		perror("fork");
		return -1;
	}

	close(fd);
	return 0;
}
#endif
