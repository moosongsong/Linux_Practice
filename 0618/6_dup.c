// 6_dup.c
// 표준 출력을 일반 파일로 리다이렉션하는 코드를 생각해 봅시다.
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

	int fd = open(*argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	// 표준 출력 -> fd
	close(1);	// 모니터 닫기
	dup(fd);	// 현재 파일 정보를 fd_table에서 비어 있는 가장 작은 곳에 복제
	printf("hello, world\n");

	close(fd);
	return 0;
}


