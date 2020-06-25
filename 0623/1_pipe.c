// 1_pipe.c
#if 0
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
enum { READ, WRITE };

int main() {
	int pfd[2];
	if (pipe(pfd) == -1) {
		perror("pipe");
		return -1;
	}
	
	char buf[BUFSIZ];
	pid_t pid = fork();
	if (pid > 0) {	// parent
		// 부모는 키보드로부터 입력 받은 데이터를 자식에게 전송할 것이므로
		// 파이프의 읽기 디스크립터는 필요가 없습니다. 필요 없는 디스크립터는
		// 닫아주는 것이 좋습니다.
		close(pfd[READ]);

		while (1) {
			// 키보드로부터 데이터를 읽습니다.
			int nRead = read(0, buf, sizeof(buf));
			if (nRead < 0) {
				perror("read");
				return -1;
			}
			else if (nRead == 0) { // EOF
				break;
			}
			// 읽은 데이터를 파이프에 씁니다.
			write(pfd[WRITE], buf, nRead);
		}
		close(pfd[WRITE]);
	}
	else if (pid == 0) {	// child
		close(pfd[WRITE]);

		while (1) {
			// 파이프로부터 데이터를 읽어옵니다.
			int nRead = read(pfd[READ], buf, sizeof(buf));
			if (nRead < 0) {
				perror("read");
				return -1;
			}
			else if (nRead == 0 ) { // EOF
				break;
			}
			buf[nRead-1] = 0;
			printf("%s\n", buf);
		}
		close(pfd[READ]);
	}
	else {	// ERROR
		perror("fork");
		return -1;
	}
	return 0;
}

#endif

#if 0
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
enum { READ, WRITE };

// argv[0] argv[1] argv[2]
// ./a.out ls      wc
int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s cmd1 cmd2\n", *argv);
		return -1;
	}
	const char *cmd1 = argv[1];
	const char *cmd2 = argv[2];

	int pfd[2];
	if (pipe(pfd) == -1) {
		perror("pipe");
		return -1;
	}

	// ls | wc
	pid_t pid = fork();
	if (pid > 0) {	// ls
		close(pfd[READ]);

		close(1);					// close(fd_table[1]);
		dup(pfd[WRITE]);	// fd_table[1] = fd_table[4];
		close(pfd[WRITE]);// close(fd_table[4]);
		execlp(cmd1, cmd1, (char *)0);
		return -1;
	}
	else if (pid == 0) {	// wc
		close(pfd[WRITE]);

		close(0);
		dup(pfd[READ]);
		close(pfd[READ]);
		execlp(cmd2, cmd2, (char *)0);
		return -1;
	}
	else {
		perror("fork");
		return -1;
	}
	return 0;
}

#endif



// C 표준 라이브러리는 파이프를 사용하여 서로 다른 프로세스의 통신을 쉽게
// 할 수 있도록 popen 함수를 제공합니다.
#include <stdio.h>

// ./a.out ls wc
int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s cmd1 cmd2\n", *argv);
		return -1;
	}
	const char *cmd1 = argv[1];
	const char *cmd2 = argv[2];

	FILE *src = popen(cmd1, "r");	// FILE *src = popen("ls", "r");
	if (src == NULL) {
		perror("popen");
		return -1;
	}

	FILE *dst = popen(cmd2, "w");	// FILE *dst = popen("wc", "w");
	if (dst == NULL) {
		perror("popen");
		return -1;
	}

	char buf[BUFSIZ];
	while (1) {
		if (fgets(buf, sizeof(buf), src) == NULL) {
			if (ferror(src)) {
				perror("fgets");
				return -1;
			}
			else if (feof(src)) {
				break;
			}
		}
		fputs(buf, dst);
	}
	pclose(dst);
	pclose(src);
	return 0;
}

