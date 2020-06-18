
// a.out a.c == cat
#if 0
#include <stdio.h>
#include <unistd.h>	// usleep

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

	while (1) {
		int ch = fgetc(fp);
		if (ch == EOF)
			break;
		
		usleep(100000);
		fputc(ch, stdout);
		fflush(stdout);
	}
	
	fclose(fp);
	return 0;
}
#endif

#if 0
// 이전의 코드는 바이트 단위로 입출력을 수행하기 때문
// 성능 상의 이슈가 존재합니다. 이를 해결하기 위해 버퍼를 도입합니다.
#include <stdio.h>
#include <unistd.h>	// usleep

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

	char buf[4096];	// 4KB
	while (1) {
		if (fgets(buf, sizeof(buf), fp) == NULL)	// int ch = fgetc(fp);
			break;
		
		usleep(100000);
		fputs(buf, stdout);							// fputc(ch, stdout);
		fflush(stdout);
	}
	
	fclose(fp);
	return 0;
}
#endif

#if 1
// 이전의 코드는 라인 버퍼를 사용하므로 다소 빠르게 동작합니다.
// 하지만 버퍼 전체를 온전히 사용하는 것이 아니므로 성능 상의 이슈는
// 여전이 존재하게 됩니다. 이를 해결하기 위해 fully-buffered를 도입합니다.
#include <stdio.h>
#include <unistd.h>	// usleep
#include <errno.h>

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

	char buf[4096];	// 4KB
	while (1) {
		int nRead = fread(buf, sizeof(char), sizeof(buf), fp);
		//                     원소의 크기   배열의 길이
		perror("fread");
		if (nRead) {
			usleep(100000);
			fwrite(buf, sizeof(char), nRead, stdout);
			//          원소의 크기   배열의 길이
			fflush(stdout);
		}
		else {
			break;
		}
	}

	fclose(fp);
	return 0;
}
#endif
