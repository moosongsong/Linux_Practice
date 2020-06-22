
#if 0
// int execl(const char *path, const char *arg, .../* (char  *) NULL */);
#include <stdio.h>
#include <unistd.h>

int main() {
	if (execl("./test", "test", "hello", "world", (char *)NULL) == -1)
		perror("execl");

	printf("dead code...\n");
	return 0;
}
#endif

#if 0
#include <stdio.h>
#include <unistd.h>

int main() {
	char *args[] = { "test", "hello", "world", (char *)NULL};
	if (execv("./test", args) == -1)
		perror("execl");

	printf("dead code...\n");
	return 0;
}
#endif

#if 1
#include <unistd.h>

int main() {
	// execlp("vim", "vim", "./test.c", (char *)NULL);

	char *args[] = {"vim", "./test.c", (char *)NULL };
	execvp("vim", args);
	return 0;
}
#endif

