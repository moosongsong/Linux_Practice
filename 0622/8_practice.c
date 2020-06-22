// 8_practice.c
#if 0
#include <stdio.h>
#include <stdlib.h>

int main() {
	system("clear");
	printf("hello, world\n");
	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int my_system(const char *cmd) {
	if (cmd == NULL) {
		fprintf(stderr, "my_system: argument is null\n");
		return -1;
	}

	pid_t pid = fork();
	if (pid > 0) {
		if (waitpid(pid, NULL, 0) == -1)
			return -1;
	}
	else if (pid == 0) {
		execlp(cmd, cmd, (char *)NULL);
		exit(1);
	}
	else {
		perror("fork");
		return -1;
	}
	return 0;
}

int main() {
	my_system("clear");	// system("clear");
	printf("hello, world\n");
	return 0;
}
#endif


#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char buf[BUFSIZ];
	while (1) {			
		printf("%% ");
		fgets(buf, sizeof(buf), stdin);
		buf[strlen(buf) - 1] = '\0';

		pid_t pid = fork();
		if (pid > 0) {
			if (waitpid(pid, NULL, 0) == -1)
				exit(1);
		}
		else if (pid == 0) {
			execlp(buf, buf, (char *)NULL);
			exit(1);	
		}
		else {	// pid < 0
			perror("fork");
			exit(1);
		}	
	}
}











