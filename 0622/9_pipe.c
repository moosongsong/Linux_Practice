// 9_pipe.c
#include <unistd.h>
#include <stdio.h>
enum { READ, WRITE };
int main() {
	int pfd[2]; // int pipe(int pipefd[2]);
	if (pipe(pfd) == -1) {
		perror("pipe");
		return -1;
	}
	write(pfd[WRITE], "hello", 5);

	char buf[BUFSIZ];
	int nRead = read(pfd[READ], buf, sizeof(buf));
	if (nRead < 0) {
		perror("read");
		return -1;
	}
	buf[nRead] = '\0';
	printf("%s\n", buf);

	return 0;
}
