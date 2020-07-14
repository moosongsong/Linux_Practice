
#if 1
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	}
	--argc, ++argv;

	struct stat sb = {0,};
	if (lstat(*argv, &sb) == -1) {
		perror("lstat");
		return -1;
	}

	printf("%ld %s\n", sb.st_nlink, *argv);
	return 0;
}
#endif








