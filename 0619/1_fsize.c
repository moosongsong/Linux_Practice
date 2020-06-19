// 1_fsize.c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/sysmacros.h>

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
	
	// 	if (((sb.st_mode & S_IFMT) == S_IFBLK) || ((sb.st_mode & S_IFMT) == S_IFCHR))
 	if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode))
		// printf("%lu, %lu ", (sb.st_rdev >> 8) & 0xFF, sb.st_rdev & 0xFF);
		printf("%u, %u ", major(sb.st_rdev), minor(sb.st_rdev));
	else
		printf("%ld ", sb.st_size);

	printf("%s\n", *argv);
	return 0;
}

