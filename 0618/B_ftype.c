// 8_ftype.c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
// usage: ./a.out hello.txt

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	}
	--argc, ++argv;

	// int lstat(const char *pathname, struct stat *statbuf);
	struct stat sb = {0,};
	if (lstat(*argv, &sb) == -1) {
		perror("lstat");
		return -1;
	}

	// printf("%d, %X\n", sb.st_mode, sb.st_mode);
	switch (sb.st_mode & S_IFMT) {
		case S_IFBLK:  printf("b: block device\n");            break;
		case S_IFCHR:  printf("c: character device\n");        break;
		case S_IFDIR:  printf("d: directory\n");               break;
		case S_IFIFO:  printf("p: FIFO/pipe\n");               break;
		case S_IFLNK:  printf("l: symlink\n");                 break;
		case S_IFREG:  printf("-: regular file\n");            break;
		case S_IFSOCK: printf("s: socket\n");                  break;
		default:       printf("unknown?\n");                break;
	}

	return 0;
}
