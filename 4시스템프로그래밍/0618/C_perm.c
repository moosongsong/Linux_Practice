#if 0
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
	// 연습 문제. 아래의 코드를 개선하여 간단하게 구현해 보세요 :D
	// 012345678A
	// Trwxrwxrwx
	char perm[11] = {0,};
	perm[0] = ' ';	// file type

	// user
	perm[1] = (sb.st_mode & S_IRUSR) ? 'r' : '-';
	perm[2] = (sb.st_mode & S_IWUSR) ? 'w' : '-';
	perm[3] = (sb.st_mode & S_IXUSR) ? 'x' : '-';

	// group
	perm[4] = (sb.st_mode & S_IRGRP) ? 'r' : '-';
	perm[5] = (sb.st_mode & S_IWGRP) ? 'w' : '-';
	perm[6] = (sb.st_mode & S_IXGRP) ? 'x' : '-';
	
	// other
	perm[7] = (sb.st_mode & S_IROTH) ? 'r' : '-';
	perm[8] = (sb.st_mode & S_IWOTH) ? 'w' : '-';
	perm[9] = (sb.st_mode & S_IXOTH) ? 'x' : '-';

	printf("%s %s\n", perm, *argv);
	return 0;
}
#endif


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
	// 연습 문제. 아래의 코드를 개선하여 간단하게 구현해 보세요 :D
	//             012345678A
	//             Trwxrwxrwx
	char perm[] = " ---------";
	char rwx[] = "rwx";
	for (int i = 0; i < 9; i++) {
		if ((sb.st_mode >> (8 - i)) & 0x1)
			perm[i + 1] = rwx[i % 3];
	}

	printf("%s %s\n", perm, *argv);
	return 0;
}
#endif








