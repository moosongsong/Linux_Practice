// 7_dup.c
// dup 함수로 복제된 파일 디스크립터와 기존 파일 디스크립터에 대하여
// 읽기를 수행해 봅니다.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	}
	--argc, ++argv;

	int fd = open(*argv, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	close(0);	// 키보드 닫기
	dup(fd);	

	char buf1[32] = {0,};
	read(fd, buf1, 5);

	char buf2[32] = {0,};
	read(0, buf2, 5);

	printf(" 0: %s\n", buf2);
	printf("fd: %s\n", buf1);

	close(fd);
	return 0;
}


