// 0_owner.c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>

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

	struct passwd *pswd = getpwuid(sb.st_uid);	// /etc/passwd
	if (pswd == NULL) {
		perror("getpwuid");
		return -1;
	}

	struct group *grp = getgrgid(sb.st_gid);	// /etc/group
	if (grp == NULL) {
		perror("getgrgid");
		return -1;
	}

	// printf("%d ", sb.st_uid);
	// printf("%d ", sb.st_gid);
	printf("%s %s %s\n", pswd->pw_name, grp->gr_name, *argv);
	return 0;
}

