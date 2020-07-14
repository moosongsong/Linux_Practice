// 8_dup.c
// 파일 디스크립터를 복제한 다음 기존 파일 디스크립터를 삭제해 봅니다.
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

	int fd = open(*argv, O_RDONLY); 	// 참조 계수: 1
	if (fd < 0) {
		perror("open");
		return -1;
	}

	close(0);	// 키보드 닫기
	dup(fd);	// 참조 계수: 2
	close(fd);	// 참조 계수: 1

	char buf[32] = {0,};
	read(0, buf, 5);

	printf("%s\n", buf);
	return 0;
}


