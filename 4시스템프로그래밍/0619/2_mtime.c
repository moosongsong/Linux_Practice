// 2_mtime.c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
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

	// yyyy-MM-dd hh:mm:ss
	// printf("%lu ", sb.st_mtime);

	char mtime[32] = {0,};
	struct tm *t = localtime(&sb.st_mtime);
// 	sprintf(mtime, "%04d-%02d-%02d %02d:%02d:%02d",
// 			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
// 			t->tm_hour, t->tm_min, t->tm_sec);

	strftime(mtime, sizeof(mtime), "%b %e %R ", t);
	printf("%s %s\n", mtime, *argv);
	return 0;
}

