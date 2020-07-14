// 4_mycat.c
#include <stdio.h>
#include <stdlib.h>	// exit();

// long getFileSize(FILE *fp) {
// 	if (fp == NULL) {
// 		fprintf(stderr, "getFileSize: argument is null\n");
// 		return -1;
// 	}
// 
// 	if (fseek(fp, 0, SEEK_END) == -1) {
// 		perror("fseek");
// 		return -1;
// 	}
// 
// 	long fsize = ftell(fp);
// 	if (fsize == -1) {
// 		perror("ftell");
// 		return -1;
// 	}
// 	return fsize;
// }

long getFileSize(FILE *fp) {
	if (fp == NULL) {
		fprintf(stderr, "getFileSize: argument is null\n");
		return -1;
	}

	// 1. 현재 파일 옵셋을 저장
	long oldPos = ftell(fp);
	if (oldPos == -1) {
		perror("ftell");
		return -1;
	}

	// 2. 옵셋을 끝까지 이동하여 파일의 크기를 계산
	if (fseek(fp, 0, SEEK_END) == -1) {
		perror("fseek");
		return -1;
	}

	long fsize = ftell(fp);
	if (fsize == -1) {
		perror("ftell");
		return -1;
	}

	// 3. 이전 파일 옵셋으로 복원
	if (fseek(fp, oldPos, SEEK_SET) == -1) {
		perror("fseek");
		exit(-1);
	}
	return fsize;
}

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

	long fsize = getFileSize(fp);
	if (fsize < 0) {
		return -1;
	}
	printf("# FILE SIZE: %ld\n", fsize);

	char buf[4096];	
	while (1) {
		int nRead = fread(buf, sizeof(char), sizeof(buf), fp);
		if (nRead) {
			fwrite(buf, sizeof(char), nRead, stdout);
			fflush(stdout);
		}
		else {
			break;
		}
	}

	fclose(fp);
	return 0;
}


