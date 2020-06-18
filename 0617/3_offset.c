// 3_offset.c
#include <stdio.h>

// ./a.out hello.c
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILENAME\n", *argv);
		return -1;
	}
	--argc, ++argv;

	FILE *fp = fopen(*argv, "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}

	// int fseek(FILE *stream, long offset, int whence);
	if (fseek(fp, 0, SEEK_END) == -1) {
		perror("fseek");
		return -1;
	}

	long fsize = ftell(fp);
	if (fsize == -1) {
		perror("ftell");
		return -1;
	}
	printf("%ld\n", fsize);

	fclose(fp);
	return 0;
}
