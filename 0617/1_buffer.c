// 1_buffer.c
#if 0
#include <unistd.h>
#include <stdio.h>

int main() {
	printf("hello, world");
	fflush(stdout);
	sleep(-1);	// 136년 후에 깨어나게 됨
	return 0;
}
#endif

#include <stdio.h>

void flush_stdin() {
	int ch;
	do {
		ch = getchar();
	} while(ch != EOF && ch != '\n');
}

int main() {
	int i; scanf("%d", &i);
	flush_stdin();	// fflush(stdin);

	char c; scanf("%c", &c);

	printf("%d, %c\n", i, c);
	return 0;
}















