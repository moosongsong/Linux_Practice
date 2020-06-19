// 2_mtime.c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <time.h>  // <---

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	}
	--argc, ++argv;

	struct stat sb;
	if (lstat(*argv, &sb) == -1) {
		perror("lstat");
		return -1;
	}

	if (S_ISLNK(sb.st_mode)) { // if ((sb.st_mode & S_IFMT) == SIFLNK)
		char symlink[256];
		ssize_t ret = readlink(*argv, symlink, sizeof(symlink));
		symlink[ret] = '\0';
		printf("%s -> %s\n", *argv, symlink);
	}
	else 
		printf("%s\n", *argv);

	return 0;
}

// 연습 문제! 지금까지 구현된 기능을 합쳐 하나의 프로그램으로 구현해 보세요 :D
// $ ./a.out a.txt
// -rw-r--r-- 1 linux linux 144 Jun 17 23:59 a.txt



